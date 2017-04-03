/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 15:15:12 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/03 18:00:33 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_shell.h"
#include "sh_errors.h"
#include "ft_program.h"
#include "ft_streams.h"
#include "ft_debug.h"

int			main(int argc, char *argv[], char *envp[])
{
	t_sh_env	env;
	int			status;

	(void)argc;
	FT_DEBUG("main: init program '%s'", argv[0]);
	ft_setprogname(argv[0]);
	g_ft_strerror = &sh_strerror;
	ft_setvbuf(FT_STDIN, NULL, FT_IONBF, 0);
	ft_setvbuf(FT_STDERR, NULL, FT_IONBF, 0);
	if (sh_shell_start(&env, envp) != 0)
	{
		FT_DEBUG("main: init failed");
		return (ft_cleanup(FT_EXIT_FAILURE));
	}
	while (sh_shell_prompt(&env) == 0)
		;
	status = sh_shell_end(&env);
	FT_DEBUG("main: exit with '%d'", status);
	return (ft_cleanup(status));
}
