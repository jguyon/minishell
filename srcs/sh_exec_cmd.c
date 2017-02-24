/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 00:21:28 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/25 00:44:13 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_exec.h"
#include "sh_errors.h"
#include "ft_memory.h"

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

int			sh_exec_cmd(t_sh_env *env, t_sh_cmd *cmd)
{
	char	**argv;
	int		err;

	if (!(argv = sh_cmd_toargv(&cmd)))
		return (SH_ERR_NOMEM);
	err = sh_env_exec(env, argv);
	del_argv(argv);
	return (err);
}
