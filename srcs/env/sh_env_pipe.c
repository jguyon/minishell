/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 16:39:01 by jguyon            #+#    #+#             */
/*   Updated: 2017/05/04 17:48:20 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "ft_streams.h"
#include "ft_program.h"
#include "ft_debug.h"

static t_sh_err	dup_fds(int fds[2])
{
	t_sh_err	err;

	err = SH_ERR_OK;
	if (dup2(fds[0], 0) == -1 || dup2(fds[1], 1) == -1)
		err = SH_ERR_IO;
	if (fds[0] != 0)
		close(fds[0]);
	if (fds[1] != 1)
		close(fds[1]);
	return (err);
}

t_sh_err		sh_env_pipe(t_sh_env *env, char *const argv[],
					int fds[2], pid_t *child)
{
	t_sh_err	err;

	FT_ASSERT(env != NULL);
	FT_ASSERT(argv != NULL && argv[0] != NULL);
	FT_ASSERT(fds && fds[0] >= 0 && fds[1] >= 0);
	FT_ASSERT(child != NULL);
	ft_fflush(NULL);
	*child = fork();
	if (*child < 0)
		return (SH_ERR_IO);
	if (*child == 0)
	{
		if ((err = dup_fds(fds)) || (err = sh_env_exec(env, argv)))
			ft_error(SH_EXIT_NOFORK, err, "%s", argv[0]);
		ft_exit(sh_env_status(env));
		return (err);
	}
	return (SH_ERR_OK);
}
