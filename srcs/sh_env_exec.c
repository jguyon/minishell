/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 01:31:39 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/03 17:16:45 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "sh_errors.h"
#include "ft_memory.h"
#include "ft_debug.h"

int		sh_env_exec(t_sh_env *env, char *const argv[])
{
	t_sh_builtin	*builtin;
	char			*binpath;
	int				err;

	FT_ASSERT(env != NULL);
	FT_ASSERT(argv != NULL);
	FT_ASSERT(argv[0]);
	err = 0;
	builtin = NULL;
	binpath = NULL;
	if ((err = sh_env_builtin(env, argv[0], &builtin)) == 0)
		env->exit_status =
			SH_EXIT_STATUS(sh_env_exec_builtin(env, builtin, argv));
	else if ((err = sh_env_binpath(env, argv[0], &binpath)) == 0)
		env->exit_status = SH_EXIT_STATUS(sh_env_exec_bin(env, binpath, argv));
	else if (err == SH_ERR_NOPERM)
		env->exit_status = SH_EXIT_NOEXEC;
	else
		env->exit_status = SH_EXIT_NOTFOUND;
	ft_memdel((void **)&binpath);
	return (err);
}
