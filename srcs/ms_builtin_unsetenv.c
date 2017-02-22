/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_unsetenv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 19:34:30 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/22 19:37:21 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "ms_errors.h"
#include "ft_program.h"

int		ms_builtin_unsetenv(int ac, char *const av[], t_env *env)
{
	if (ac < 2)
	{
		ms_error(0, 0, "%s: Too few arguments", av[0]);
		return (FT_EXIT_FAILURE);
	}
	if (ac > 2)
	{
		ms_error(0, 0, "%s: Too many arguments", av[0]);
		return (FT_EXIT_FAILURE);
	}
	ms_env_unset(env, av[1]);
	return (FT_EXIT_SUCCESS);
}
