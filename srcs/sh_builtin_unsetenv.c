/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_unsetenv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 02:30:40 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/25 02:32:56 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_builtins.h"
#include "sh_errors.h"
#include "ft_program.h"

int		sh_builtin_unsetenv(int ac, char *const av[], t_sh_env *env)
{
	if (ac < 2)
	{
		ft_error(0, SH_ERR_ARGS2SMALL, "%s", av[0]);
		return (FT_EXIT_FAILURE);
	}
	if (ac > 2)
	{
		ft_error(0, SH_ERR_ARGS2BIG, "%s", av[0]);
		return (FT_EXIT_FAILURE);
	}
	sh_env_unsetvar(env, av[1]);
	return (FT_EXIT_SUCCESS);
}
