/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_setenv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 02:23:01 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/25 02:26:29 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_builtins.h"
#include "sh_errors.h"
#include "ft_program.h"
#include "ft_streams.h"

static void	print_env(t_sh_env *env)
{
	size_t		i;
	char *const	*envp;

	if ((envp = sh_env_vars(env)))
	{
		i = 0;
		while (envp[i])
		{
			ft_fputs(envp[i], FT_STDOUT);
			ft_fputc('\n', FT_STDOUT);
			++i;
		}
	}
}

int			sh_builtin_setenv(int ac, char *const av[], t_sh_env *env)
{
	if (ac > 3)
	{
		ft_error(0, SH_ERR_ARGS2BIG, "%s", av[0]);
		return (FT_EXIT_FAILURE);
	}
	if (ac == 1)
	{
		print_env(env);
		return (FT_EXIT_SUCCESS);
	}
	if (sh_env_setvar(env, av[1], av[2] ? av[2] : NULL))
	{
		ft_error(0, SH_ERR_NOMEM, "%s", av[0]);
		return (FT_EXIT_FAILURE);
	}
	return (FT_EXIT_SUCCESS);
}
