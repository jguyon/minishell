/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_shell_start.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 15:12:14 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/25 15:43:36 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_shell.h"
#include "sh_errors.h"
#include "ft_program.h"
#include "ft_memory.h"
#include <unistd.h>

static int	set_path(t_sh_env *env)
{
	if (sh_env_getvar(env, "PATH"))
		return (0);
	return (sh_env_setvar(env, "PATH", SH_DEFAULT_PATH));
}

static int	set_pwd(t_sh_env *env)
{
	const char	*envpwd;
	char		*syspwd;
	int			err;

	if ((envpwd = sh_env_getvar(env, "PWD")) && !chdir(envpwd))
		return (0);
	if (!(syspwd = getcwd(NULL, 0)))
		return (SH_ERR_IO);
	err = sh_env_setvar(env, "PWD", syspwd);
	ft_memdel((void **)&syspwd);
	return (err);
}

static int	set_home(t_sh_env *env)
{
	const char	*pwd;
	int			err;

	if (sh_env_getvar(env, "HOME"))
		return (0);
	if ((pwd = sh_env_getvar(env, "PWD"))
		&& (err = sh_env_setvar(env, "HOME", pwd)))
		return (err);
	return (0);
}

static int	set_prompt(t_sh_env *env)
{
	if (sh_env_getvar(env, "PS1"))
		return (0);
	return (sh_env_setvar(env, "PS1", SH_DEFAULT_PS1));
}

int			sh_shell_start(t_sh_env *env, char *const envp[])
{
	int		err;

	if ((err = sh_env_start(env, envp)))
	{
		ft_error(0, err, NULL);
		return (-1);
	}
	if ((err = set_path(env))
		|| (err = set_pwd(env))
		|| (err = set_home(env))
		|| (err = set_prompt(env)))
	{
		ft_error(0, err, NULL);
		sh_env_end(env);
		return (-1);
	}
	return (0);
}
