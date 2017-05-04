/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_shell_start.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 15:12:14 by jguyon            #+#    #+#             */
/*   Updated: 2017/05/04 17:55:58 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_shell.h"
#include "ft_program.h"
#include "ft_memory.h"
#include "ft_debug.h"
#include <unistd.h>

static t_sh_err	set_path(t_sh_env *env)
{
	if (sh_env_getvar(env, "PATH"))
		return (SH_ERR_OK);
	return (sh_env_setvar(env, "PATH", SH_DEFAULT_PATH));
}

static t_sh_err	set_pwd(t_sh_env *env)
{
	const char	*envpwd;
	char		*syspwd;
	t_sh_err	err;

	if ((envpwd = sh_env_getvar(env, "PWD")) && !sh_env_chdir(env, envpwd, 0))
		return (SH_ERR_OK);
	if (!(syspwd = getcwd(NULL, 0)))
		return (SH_ERR_IO);
	err = sh_env_setvar(env, "PWD", syspwd);
	ft_memdel((void **)&syspwd);
	return (err);
}

static t_sh_err	set_home(t_sh_env *env)
{
	const char	*pwd;
	t_sh_err		err;

	if (sh_env_getvar(env, "HOME"))
		return (SH_ERR_OK);
	if ((pwd = sh_env_getvar(env, "PWD"))
		&& (err = sh_env_setvar(env, "HOME", pwd)))
		return (err);
	return (SH_ERR_OK);
}

static t_sh_err	set_prompt(t_sh_env *env)
{
	if (sh_env_getvar(env, "PS1"))
		return (SH_ERR_OK);
	return (sh_env_setvar(env, "PS1", SH_DEFAULT_PS1));
}

int				sh_shell_start(t_sh_env *env, char *const envp[])
{
	t_sh_err	err;

	FT_ASSERT(env != NULL);
	FT_ASSERT(envp != NULL);
	FT_DEBUG("shell: init shell with env '%p'", env);
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
