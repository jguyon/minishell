/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_binpath.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 22:20:29 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/23 23:55:09 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "sh_errors.h"
#include "ft_strings.h"
#include "ft_memory.h"
#include <unistd.h>

static char	*join_paths(const char *dir, size_t dirlen,
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

static int	check_absolute(const char *name, char **path)
{
	if (!(*path = ft_strdup(name)))
		return (SH_ERR_NOMEM);
	if (access(name, X_OK) == 0)
		return (0);
	if (access(*path, F_OK) == 0)
	{
		ft_memdel((void **)path);
		return (SH_ERR_NOPERM);
	}
	ft_memdel((void **)path);
	return (SH_ERR_NOTFOUND);
}

static int	check_paths(const char *envpaths, const char *name, char **path)
{
	const char	*start;
	const char	*end;

	start = envpaths;
	while (*start && (end = ft_strchrnul(start, ':')))
	{
		if (!(*path = join_paths(start, end - start, name, ft_strlen(name))))
			return (SH_ERR_NOMEM);
		if (access(*path, X_OK) == 0)
			return (0);
		if (access(*path, F_OK) == 0)
		{
			ft_memdel((void **)path);
			return (SH_ERR_NOPERM);
		}
		ft_memdel((void **)path);
		start = *end == '\0' ? end : end + 1;
	}
	return (SH_ERR_NOTFOUND);
}

int			sh_env_binpath(t_sh_env *env, const char *name, char **path)
{
	const char	*envpaths;

	*path = NULL;
	if (ft_strchr(name, '/'))
		return (check_absolute(name, path));
	if (!(envpaths = sh_env_getvar(env, "PATH")))
		return (SH_ERR_NOTFOUND);
	return (check_paths(envpaths, name, path));
}
