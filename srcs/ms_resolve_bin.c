/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_resolve_bin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 19:00:50 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/17 20:44:39 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include "ft_memory.h"
#include "ft_strings.h"
#include <unistd.h>

static t_bin	*find_bin(t_dlist *bins, const char *path, const char *name)
{
	t_dlist_node	*node;
	t_bin			*bin;

	node = ft_dlst_first(bins);
	while (node)
	{
		bin = FT_DLST_ENTRY(bins, node);
		if (ft_strcmp(bin->name, name) == 0)
		{
			ft_dlst_remove(node);
			if (bin->old_path != path)
			{
				ft_memdel((void **)&bin);
				return (NULL);
			}
			ft_dlst_pushl(bins, node);
			return (bin);
		}
		node = ft_dlst_next(bins, node);
	}
	return (NULL);
}

static char		*join_path(const char *dir, size_t dirlen, const char *name)
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

static t_bin	*create_bin(t_dlist *bins, const char *path, const char *name)
{
	const char	*start;
	const char	*end;
	char		*file;
	t_bin		*bin;

	start = path;
	while (*start)
	{
		end = ft_strchrnul(start, ':');
		if ((file = join_path(start, end - start, name)) && !access(file, F_OK)
			&& (bin = (t_bin *)ft_memalloc(sizeof(*bin))))
		{
			bin->old_path = path;
			bin->name = ft_strrchr(file, '/');
			bin->file = file;
			ft_dlst_pushl(bins, &(bin->node));
			return (bin);
		}
		ft_memdel((void **)&file);
		start = *end ? end + 1 : end;
	}
	return (NULL);
}

const char		*ms_resolve_bin(t_env *env, const char *name)
{
	const char	*path;
	t_bin		*bin;

	if (!(path = ms_env_get(env, "PATH")))
		return (NULL);
	if (!(bin = find_bin(&(env->bins), path, name)))
		bin = create_bin(&(env->bins), path, name);
	return (bin ? bin->file : NULL);
}
