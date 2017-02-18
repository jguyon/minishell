/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 15:15:12 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/18 22:59:15 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_env.h"
#include "ms_errors.h"
#include "ft_program.h"
#include "ft_streams.h"

static void	clean_env(int status, void *env)
{
	(void)status;
	ms_env_end(env);
}

static void	clean_cmd(int status, void *cmdp)
{
	(void)status;
	ms_destroy_cmd(cmdp);
}

int			main(int argc, char *argv[], char *envp[])
{
	t_env	env;
	t_cmd	*cmd;

	(void)argc;
	ft_setprogname(argv[0]);
	ft_setvbuf(FT_STDIN, NULL, FT_IONBF, 0);
	if (ms_env_start(&env, envp))
		ms_error(FT_EXIT_FAILURE, MS_ERR_NOMEM, NULL);
	ft_onexit(&clean_env, &env);
	cmd = NULL;
	ft_onexit(&clean_cmd, &cmd);
	while (!ft_feof(FT_STDIN))
	{
		ft_fputs("$ ", FT_STDERR);
		if ((cmd = ms_parse_cmd(FT_STDIN)) && !ft_feof(FT_STDIN))
		{
			ms_exec_cmd(cmd, &env);
			ms_destroy_cmd(&cmd);
		}
		else if (ft_feof(FT_STDIN))
			ft_fputc('\n', FT_STDERR);
	}
	return (ft_cleanup(FT_EXIT_SUCCESS));
}
