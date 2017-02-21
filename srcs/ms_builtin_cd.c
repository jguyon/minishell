/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 12:47:31 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/21 22:41:17 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "ms_errors.h"
#include "ft_program.h"
#include "ft_strings.h"
#include <unistd.h>
#include <stdlib.h>

static const char	*get_new_pwd(char *const av[], t_env *env)
{
	const char	*pwd;

	if (!av[1])
	{
		if (!(pwd = ms_env_get(env, "HOME")))
			ms_error(0, 0, "%s: %s", av[0], "HOME not set");
	}
	else if (ft_strcmp(av[1], "-") == 0)
	{
		if (!(pwd = ms_env_get(env, "OLDPWD")))
			ms_error(0, 0, "%s: %s", av[0], "OLDPWD not set");
	}
	else
		pwd = av[1];
	return (pwd);
}

int					ms_builtin_cd(int ac, char *const av[], t_env *env)
{
	char		*oldpwd;
	char		*newpwd;
	const char	*dir;

	(void)ac;
	if (!(oldpwd = getcwd(NULL, 0)))
	{
		ms_error(0, MS_ERR_IO, "%s", av[0]);
		return (FT_EXIT_FAILURE);
	}
	else if (!(dir = get_new_pwd(av, env)))
		return (FT_EXIT_FAILURE);
	else if (chdir(dir))
	{
		free(oldpwd);
		ms_error(0, MS_ERR_NOTDIR, "%s", av[0]);
		return (FT_EXIT_FAILURE);
	}
	ms_env_set(env, "OLDPWD", oldpwd);
	ms_env_set(env, "PWD", (newpwd = getcwd(NULL, 0)) ? newpwd : dir);
	free(newpwd);
	free(oldpwd);
	return (FT_EXIT_SUCCESS);
}
