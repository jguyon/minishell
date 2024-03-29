/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_chdir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 01:48:26 by jguyon            #+#    #+#             */
/*   Updated: 2017/05/04 17:41:04 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "sh_files.h"
#include "ft_memory.h"
#include "ft_debug.h"
#include <unistd.h>

static t_sh_err	get_newwd(const char *cwd, const char *path, char **newwd)
{
	t_sh_err	err;
	char		*joined;

	*newwd = NULL;
	joined = NULL;
	if (path[0] == '/')
	{
		if ((err = sh_path_canonical(path, newwd)))
			return (err);
	}
	else if ((err = sh_path_join(cwd, path, &joined))
		|| (err = sh_path_canonical(joined, newwd)))
	{
		ft_memdel((void **)&joined);
		return (err);
	}
	ft_memdel((void **)&joined);
	if ((err = sh_check_dir(*newwd)))
		ft_memdel((void **)newwd);
	return (err);
}

static t_sh_err	change_dir(t_sh_env *env, char *path, int nosym)
{
	if (chdir(path))
	{
		ft_memdel((void **)&path);
		return (SH_ERR_IO);
	}
	if (nosym)
	{
		ft_memdel((void **)&path);
		if (!(path = getcwd(NULL, 0)))
			return (SH_ERR_IO);
	}
	ft_memdel((void **)&(env->cwd));
	env->cwd = path;
	FT_DEBUG("env: changed cwd to '%s'", env->cwd);
	return (SH_ERR_OK);
}

t_sh_err			sh_env_chdir(t_sh_env *env, const char *path, int nosym)
{
	char		*oldwd;
	char		*newwd;
	t_sh_err	err;

	FT_ASSERT(env != NULL);
	FT_ASSERT(path != NULL);
	oldwd = NULL;
	newwd = NULL;
	if ((err = sh_env_getcwd(env, nosym, &oldwd))
		|| (err = get_newwd(oldwd, path, &newwd)))
	{
		ft_memdel((void **)&oldwd);
		ft_memdel((void **)&newwd);
		return (err);
	}
	ft_memdel((void **)&oldwd);
	return (change_dir(env, newwd, nosym));
}
