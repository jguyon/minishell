/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 00:21:28 by jguyon            #+#    #+#             */
/*   Updated: 2017/05/04 17:54:31 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_exec.h"
#include "sh_errors.h"
#include "ft_memory.h"
#include "ft_program.h"
#include "ft_debug.h"

static void	del_argv(char **argv)
{
	size_t	i;

	i = 0;
	while (argv[i])
	{
		ft_memdel((void **)&(argv[i]));
		++i;
	}
	ft_memdel((void **)&argv);
}

t_sh_err	sh_exec_cmd(t_sh_env *env, t_sh_cmd **cmd)
{
	char		**argv;
	t_sh_err	err;

	FT_ASSERT(env != NULL);
	FT_ASSERT(cmd != NULL);
	FT_ASSERT(*cmd != NULL);
	if (!(argv = sh_cmd_toargv(cmd)))
		return (SH_ERR_NOMEM);
	if ((err = sh_env_exec(env, argv)))
		ft_error(0, err, "%s", argv[0]);
	del_argv(argv);
	return (SH_ERR_OK);
}
