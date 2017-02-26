/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 01:18:34 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/26 21:21:23 by jguyon           ###   ########.fr       */
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

static int			get_cwd(t_sh_env *env, char **cwd)
{
	const char	*pwd;

	if ((pwd = sh_env_getvar(env, "PWD")) && pwd[0] == '/')
	{
		if (!(*cwd = ft_strdup(pwd)))
			return (SH_ERR_NOMEM);
	}
	else
	{
		if (!(*cwd = getcwd(NULL, 0)))
			return (SH_ERR_IO);
	}
	return (0);
}

static int			get_newwd(t_sh_env *env, const char *arg,
						const char *cwd, char **pwd)
{
	const char	*dir;
	int			err;

	*pwd = NULL;
	if (!arg)
	{
		if (!(dir = sh_env_getvar(env, "HOME")))
			return (SH_ERR_NOHOME);
	}
	else if (ft_strcmp(arg, "-") == 0)
	{
		if (!(dir = sh_env_getvar(env, "OLDPWD")))
			return (SH_ERR_NOOLDPWD);
	}
	else
		dir = arg;
	if (dir[0] != '/')
	{
		if ((err = sh_path_join(cwd, dir, pwd)))
			return (err);
	}
	else if (!(*pwd = ft_strdup(dir)))
		return (SH_ERR_NOMEM);
	return (0);
}

static int			change_wd(t_sh_env *env, const char *old, const char *new)
{
	int		err;
	char	*canon;

	if (access(new, F_OK))
		return (SH_ERR_NOTDIR);
	if (access(new, X_OK))
		return (SH_ERR_NOPERM);
	if ((err = sh_path_canonical(new, &canon)))
		return (err);
	if (chdir(canon))
	{
		free(canon);
		return (SH_ERR_IO);
	}
	if ((err = sh_env_setvar(env, "PWD", canon))
		|| (err = sh_env_setvar(env, "OLDPWD", old)))
	{
		free(canon);
		return (err);
	}
	free(canon);
	return (0);
}

int					sh_builtin_cd(int ac, char *const av[], t_sh_env *env)
{
	char	*oldpwd;
	char	*newpwd;
	int		err;
	int		status;

	(void)ac;
	oldpwd = NULL;
	newpwd = NULL;
	if ((err = get_cwd(env, &oldpwd))
		|| (err = get_newwd(env, av[1], oldpwd, &newpwd))
		|| (err = change_wd(env, oldpwd, newpwd)))
	{
		ft_error(0, err, "%s", av[0]);
		status = FT_EXIT_FAILURE;
	}
	else
	{
		status = FT_EXIT_SUCCESS;
		if (av[1] && ft_strcmp(av[1], "-") == 0)
			ft_fprintf(FT_STDOUT, "%s\n", newpwd);
	}
	free(oldpwd);
	free(newpwd);
	return (status);
}
