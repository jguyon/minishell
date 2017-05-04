/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_binpath.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 22:20:29 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/04 12:57:40 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "sh_files.h"
#include "ft_strings.h"
#include "ft_memory.h"
#include "ft_debug.h"
#include <unistd.h>

static char		*join_paths(const char *dir, size_t dirlen,
				const char *name, size_t namlen)
{
	char	*filepath;

	if (dirlen == 0)
	{
		dir = ".";
		dirlen = 1;
	}
	if (dir[dirlen - 1] == '/')
		--dirlen;
	if (!(filepath = ft_strnew(dirlen + 1 + namlen)))
		return (NULL);
	ft_memcpy(filepath, dir, dirlen);
	filepath[dirlen] = '/';
	ft_memcpy(filepath + dirlen + 1, name, namlen);
	return (filepath);
}

static t_err	check_absolute(const char *name, char **path)
{
	t_err	err;

	if (!(*path = ft_strdup(name)))
		return (SH_ERR_NOMEM);
	if ((err = sh_check_bin(*path)) == SH_ERR_OK)
	{
		FT_DEBUG("env: found binary '%s'", *path);
		return (SH_ERR_OK);
	}
	ft_memdel((void **)path);
	return (err == SH_ERR_NOENT ? SH_ERR_NOCMD : err);
}

static t_err	check_paths(const char *envpaths, const char *name, char **path)
{
	const char	*start;
	const char	*end;
	t_err		err;

	start = envpaths;
	err = SH_ERR_OK;
	while (*start && (end = ft_strchrnul(start, ':')))
	{
		if (!(*path = join_paths(start, end - start, name, ft_strlen(name))))
			return (SH_ERR_NOMEM);
		if ((err = sh_check_bin(*path)) == SH_ERR_OK)
		{
			FT_DEBUG("env: found binary '%s'", *path);
			return (SH_ERR_OK);
		}
		ft_memdel((void **)path);
		start = *end == '\0' ? end : end + 1;
	}
	return (!err || err == SH_ERR_NOENT ? SH_ERR_NOCMD : err);
}

t_err			sh_env_binpath(t_sh_env *env, const char *name, char **path)
{
	const char	*envpaths;

	FT_ASSERT(env != NULL);
	FT_ASSERT(name != NULL);
	FT_ASSERT(path != NULL);
	*path = NULL;
	FT_DEBUG("env: searching for binary '%s'", name);
	if (ft_strchr(name, '/'))
		return (check_absolute(name, path));
	if (!(envpaths = sh_env_getvar(env, "PATH")) || envpaths[0] == '\0')
		return (check_paths(".", name, path));
	return (check_paths(envpaths, name, path));
}
