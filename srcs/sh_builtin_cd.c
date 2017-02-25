/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 01:18:34 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/25 01:43:47 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_builtins.h"
#include "sh_errors.h"
#include "ft_program.h"
#include "ft_strings.h"
#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>

static const char	*get_new_pwd(char *const av[], t_sh_env *env)
{
	const char	*pwd;

	if (!av[1])
	{
		if (!(pwd = sh_env_getvar(env, "HOME")))
			ft_error(0, SH_ERR_NOHOME, "%s", av[0]);
	}
	else if (ft_strcmp(av[1], "-") == 0)
	{
		if (!(pwd = sh_env_getvar(env, "OLDPWD")))
			ft_error(0, SH_ERR_NOOLDPWD, "%s", av[0]);
	}
	else
		pwd = av[1];
	return (pwd);
}

static int			set_env_vars(t_sh_env *env, char *const av[],
						const char *oldpwd, const char *newpwd)
{
	int		err;

	if ((err = sh_env_setvar(env, "OLDPWD", oldpwd))
		|| (err = sh_env_setvar(env, "PWD", newpwd)))
	{
		ft_error(0, err, "%s", av[0]);
		return (-1);
	}
	if (av[1] && ft_strcmp(av[1], "-") == 0)
		ft_fprintf(FT_STDOUT, "%s\n", newpwd);
	return (0);
}

static char			*get_curr_pwd(char *const av[])
{
	char	*pwd;

	if (!(pwd = getcwd(NULL, 0)))
	{
		ft_error(0, SH_ERR_IO, "%s", av[0]);
		return (NULL);
	}
	return (pwd);
}

static int			change_pwd(const char *dir, char *const av[])
{
	if (chdir(dir))
	{
		ft_error(0, SH_ERR_NOTDIR, "%s", av[0]);
		return (-1);
	}
	return (0);
}

int					sh_builtin_cd(int ac, char *const av[], t_sh_env *env)
{
	char		*oldpwd;
	char		*newpwd;
	const char	*dir;
	int			status;

	(void)ac;
	status = FT_EXIT_SUCCESS;
	oldpwd = NULL;
	newpwd = NULL;
	dir = NULL;
	if (!(oldpwd = get_curr_pwd(av)) || !(dir = get_new_pwd(av, env))
		|| change_pwd(dir, av) || !(newpwd = get_curr_pwd(av))
		|| set_env_vars(env, av, oldpwd, newpwd))
		status = FT_EXIT_FAILURE;
	free(newpwd);
	free(oldpwd);
	return (status);
}
