/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 16:57:20 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/18 17:14:15 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include "ms_errors.h"
#include "ft_program.h"
#include <unistd.h>
#include <sys/wait.h>

int		ms_exec_bin(t_env *env, char *path, char *const argv[])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
	{
		execve(path, argv, env->envp);
		ms_error(FT_EXIT_FAILURE, MS_ERR_NOEXEC, "%s", argv[0]);
	}
	return (0);
}
