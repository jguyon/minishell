/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 02:18:40 by jguyon            #+#    #+#             */
/*   Updated: 2017/05/04 17:46:16 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_builtins.h"
#include "ft_program.h"
#include "ft_printf.h"
#include <unistd.h>

static int	no_symlinks(int ac, char *const av[])
{
	int		nosym;
	int		opt;

	nosym = 0;
	g_ft_opterr = 0;
	g_ft_optind = 0;
	while ((opt = ft_getopt(ac, av, "LP")) != -1)
	{
		if (opt == 'L')
			nosym = 0;
		else if (opt == 'P')
			nosym = 1;
		else
		{
			ft_error(0, 0, "%s: illegal option -- %c", av[0], g_ft_optopt);
			return (-1);
		}
	}
	return (nosym);
}

int			sh_builtin_pwd(int ac, char *const av[], t_sh_env *env)
{
	int			nosym;
	char		*cwd;
	t_sh_err	err;

	if ((nosym = no_symlinks(ac, av)) < 0)
		return (FT_EXIT_FAILURE);
	if ((err = sh_env_getcwd(env, nosym, &cwd)))
	{
		ft_error(0, err, "%s", av[0]);
		return (FT_EXIT_FAILURE);
	}
	ft_fprintf(FT_STDOUT, "%s\n", cwd);
	free(cwd);
	return (FT_EXIT_SUCCESS);
}
