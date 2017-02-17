/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:22:41 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/17 21:17:20 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_errors.h"
#include "ms_env.h"
#include "ft_memory.h"
#include "ft_program.h"
#include <unistd.h>
#include <sys/wait.h>

static char	**get_argv(t_cmd *cmd, t_env *env)
{
	char			*name;
	char			**argv;
	size_t			i;
	t_dlist_node	*node;

	argv = NULL;
	if (!(name = ms_resolve_bin(env, cmd->name)) || access(name, F_OK))
		ms_error(0, MS_ERR_NOTFOUND, "%s", cmd->name);
	else if (access(name, X_OK))
		ms_error(0, MS_ERR_PERM, "%s", cmd->name);
	else if (!(argv = (char **)ft_memalloc(
				sizeof(*argv) * (cmd->arg_count + 2))))
		ms_error(FT_EXIT_FAILURE, MS_ERR_NOMEM, NULL);
	else
	{
		argv[0] = name;
		i = 0;
		node = ft_dlst_first(&(cmd->args));
		while (node)
		{
			argv[++i] = ((t_arg *)FT_DLST_ENTRY(&(cmd->args), node))->str;
			node = ft_dlst_next(&(cmd->args), node);
		}
	}
	return (argv);
}

static void	exec_argv(t_cmd *cmd, char *const *argv, t_env *env)
{
	pid_t	pid;

	if ((pid = fork()) > 0)
		waitpid(pid, NULL, 0);
	else if (pid < 0)
		ms_error(0, MS_ERR_NOEXEC, "%s", cmd->name);
	else if (execve(argv[0], argv, env->envp))
		ms_error(FT_EXIT_FAILURE, MS_ERR_NOEXEC, "%s", cmd->name);
}

void		ms_exec_cmd(t_cmd *cmd, t_env *env)
{
	char *const	*argv;

	if ((argv = get_argv(cmd, env)))
		exec_argv(cmd, argv, env);
	ft_memdel((void **)&argv);
}
