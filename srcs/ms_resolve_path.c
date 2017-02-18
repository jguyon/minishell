/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_resolve_bin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 19:00:50 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/18 17:26:18 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include "ft_memory.h"
#include "ft_strings.h"
#include <unistd.h>

static char	*join_path(const char *dir, size_t dirlen, const char *name)
{
	char	*file;

	if (dirlen == 0)
		return (NULL);
	if (dir[dirlen - 1] == '/')
		--dirlen;
	if (!(file = ft_strnew(dirlen + 1 + ft_strlen(name))))
		return (NULL);
	ft_strncpy(file, dir, dirlen);
	file[dirlen] = '/';
	ft_strcpy(file + dirlen + 1, name);
	return (file);
}

char		*ms_resolve_path(t_env *env, const char *name)
{
	const char	*envpath;
	const char	*start;
	const char	*end;
	char		*fullpath;

	if (!(envpath = ms_env_get(env, "PATH")))
		return (NULL);
	start = envpath;
	while (*start && (end = ft_strchrnul(start, ':')))
	{
		if (!(fullpath = join_path(start, end - start, name)))
			return (NULL);
		if (access(fullpath, F_OK) == 0)
			return (fullpath);
		ft_memdel((void **)&fullpath);
		start = *end ? end + 1 : end;
	}
	return (NULL);
}
