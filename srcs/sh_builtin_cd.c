/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 01:18:34 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/27 18:58:24 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_builtins.h"
#include "sh_errors.h"
#include "sh_files.h"
#include "ft_program.h"
#include "ft_printf.h"
#include "ft_strings.h"
#include <unistd.h>
#include <stdlib.h>

static int			no_symlinks(int ac, char *const av[])
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

static int			get_newwd(t_sh_env *env, const char *arg, const char **pwd)
{
	*pwd = NULL;
	if (!arg)
	{
		if (!(*pwd = sh_env_getvar(env, "HOME")))
			return (SH_ERR_NOHOME);
	}
	else if (ft_strcmp(arg, "-") == 0)
	{
		if (!(*pwd = sh_env_getvar(env, "OLDPWD")))
			return (SH_ERR_NOOLDPWD);
	}
	else
		*pwd = arg;
	return (0);
}

static int			change_wd(t_sh_env *env, const char *path,
						int nosym, int print_dir)
{
	int		err;
	char	*oldpwd;
	char	*newpwd;

	oldpwd = NULL;
	newpwd = NULL;
	if ((err = sh_env_getcwd(env, 0, &oldpwd))
		|| (err = sh_env_chdir(env, path, nosym))
		|| (err = sh_env_getcwd(env, 0, &newpwd))
		|| (err = sh_env_setvar(env, "PWD", newpwd))
		|| (err = sh_env_setvar(env, "OLDPWD", oldpwd)))
	{
		free(oldpwd);
		free(newpwd);
		return (err);
	}
	if (print_dir)
		ft_fprintf(FT_STDOUT, "%s\n", newpwd);
	free(oldpwd);
	free(newpwd);
	return (0);
}

int					sh_builtin_cd(int ac, char *const av[], t_sh_env *env)
{
	const char	*dir;
	int			err;
	int			nosym;

	dir = NULL;
	if ((nosym = no_symlinks(ac, av)) < 0)
		return (FT_EXIT_FAILURE);
	if ((err = get_newwd(env, av[g_ft_optind], &dir))
		|| (err = change_wd(env, dir, nosym,
			av[g_ft_optind] && ft_strcmp(av[g_ft_optind], "-") == 0)))
	{
		if (av[g_ft_optind])
			ft_error(0, err, "%s: %s", av[0], av[g_ft_optind]);
		else
			ft_error(0, err, "%s", av[0]);
		return (FT_EXIT_FAILURE);
	}
	return (FT_EXIT_SUCCESS);
}
