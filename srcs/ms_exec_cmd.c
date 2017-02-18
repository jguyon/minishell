/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:22:41 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/18 17:53:11 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_errors.h"
#include "ms_env.h"
#include "ft_memory.h"
#include "ft_strings.h"
#include "ft_program.h"

static char	**get_argv(char *name, size_t arg_count, t_dlist *args)
{
	char			**argv;
	size_t			i;
	t_dlist_node	*node;

	if (!(argv = (char **)ft_memalloc(sizeof(*argv) * (arg_count + 2))))
		return (NULL);
	argv[0] = name;
	i = 0;
	node = ft_dlst_first(args);
	while (node && i < arg_count)
	{
		argv[++i] = ((t_arg *)FT_DLST_ENTRY(args, node))->str;
		node = ft_dlst_next(args, node);
	}
	return (argv);
}

void		ms_exec_cmd(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**argv;

	path = NULL;
	argv = NULL;
	if (ft_strchr(cmd->name, '/'))
		path = cmd->name;
	else
		path = ms_resolve_path(env, cmd->name);
	if (!path || access(path, F_OK))
		ms_error(0, MS_ERR_NOTFOUND, "%s", cmd->name);
	else if (access(path, X_OK))
		ms_error(0, MS_ERR_NOEXEC, "%s", cmd->name);
	else if (!(argv = get_argv(cmd->name, cmd->arg_count, &(cmd->args))))
		ms_error(FT_EXIT_FAILURE, MS_ERR_NOMEM, NULL);
	else if (ms_exec_bin(env, path, argv))
		ms_error(0, MS_ERR_NOEXEC, "%s", cmd->name);
	if (path != cmd->name)
		ft_memdel((void **)&path);
	ft_memdel((void **)&argv);
}
