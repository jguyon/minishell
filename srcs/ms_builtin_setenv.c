/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_setenv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 19:01:38 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/22 19:14:14 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "ms_errors.h"
#include "ft_program.h"
#include "ft_streams.h"

static void	print_env(t_env *env)
{
	size_t	i;

	i = 0;
	while (env->envp[i])
	{
		ft_fputs(env->envp[i], FT_STDOUT);
		ft_fputc('\n', FT_STDOUT);
		++i;
	}
}

int			ms_builtin_setenv(int ac, char *const av[], t_env *env)
{
	if (ac > 3)
	{
		ms_error(0, 0, "%s: Too many arguments", av[0]);
		return (FT_EXIT_FAILURE);
	}
	if (ac == 1)
	{
		print_env(env);
		return (FT_EXIT_SUCCESS);
	}
	if (ms_env_set(env, av[1], av[2] ? av[2] : ""))
	{
		ms_error(0, MS_ERR_NOMEM, "%s", av[0]);
		return (FT_EXIT_FAILURE);
	}
	return (FT_EXIT_SUCCESS);
}
