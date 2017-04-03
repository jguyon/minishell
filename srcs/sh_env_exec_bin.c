/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_exec_bin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 00:30:54 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/03 17:15:18 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "sh_errors.h"
#include "ft_program.h"
#include "ft_debug.h"
#include <unistd.h>
#include <sys/wait.h>

int		sh_env_exec_bin(t_sh_env *env, const char *path, char *const argv[])
{
	pid_t	pid;
	int		status;

	FT_ASSERT(env != NULL);
	FT_ASSERT(path != NULL);
	FT_ASSERT(argv != NULL);
	FT_ASSERT(argv[0] != NULL);
	pid = fork();
	if (pid < 0)
		return (SH_EXIT_NOFORK);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (SH_EXIT_SIGNAL);
	}
	else
	{
		execve(path, argv, sh_env_vars(env));
		ft_error(SH_EXIT_NOEXEC, SH_ERR_NOPERM, "%s", argv[0]);
		return (SH_EXIT_NOEXEC);
	}
}
