/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_wait.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 17:04:05 by jguyon            #+#    #+#             */
/*   Updated: 2017/05/04 17:48:35 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "ft_debug.h"
#include <sys/wait.h>

#define EXIT_CODE(st) (WIFEXITED(st) ? WEXITSTATUS(st) : SH_EXIT_SIGNAL)

t_sh_err	sh_env_wait(t_sh_env *env, pid_t child)
{
	int		status;

	FT_ASSERT(env != NULL);
	FT_ASSERT(child > 0);
	if (waitpid(child, &status, 0) == -1)
	{
		env->exit_status = SH_EXIT_NOFORK;
		return (SH_ERR_IO);
	}
	env->exit_status = EXIT_CODE(status);
	return (SH_ERR_OK);
}
