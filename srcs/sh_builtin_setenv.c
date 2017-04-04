/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_setenv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 02:23:01 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/04 12:43:48 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_builtins.h"
#include "ft_program.h"
#include "ft_streams.h"

static void		print_env(t_sh_env *env)
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

static t_err	check_varname(const char *name)
{
	if (!name)
		return (0);
	if (*name < 'A' || *name > 'Z')
		return (SH_ERR_BADENV);
	while (*name)
	{
		if (!((*name >= 'A' && *name <= 'Z')
				|| (*name >= '0' && *name <= '9')
				|| *name == '_'))
			return (SH_ERR_BADENV);
		++name;
	}
	return (SH_ERR_OK);
}

int				sh_builtin_setenv(int ac, char *const av[], t_sh_env *env)
{
	t_err	err;

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
	if ((err = check_varname(av[1]))
		|| (err = sh_env_setvar(env, av[1], av[2] ? av[2] : NULL)))
	{
		ft_error(0, err, "%s: %s", av[0], av[1]);
		return (FT_EXIT_FAILURE);
	}
	return (FT_EXIT_SUCCESS);
}
