/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_path_nodots.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 16:16:42 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/03 17:22:49 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_files.h"
#include "sh_errors.h"
#include "ft_strings.h"
#include "ft_memory.h"
#include "ft_debug.h"

static int	process_element(char *root, char **curr,
				const char *start, const char *end)
{
	int		err;

	if (start[0] == '.' && start[1] == '.' && end == start + 2)
	{
		if (*curr != root)
		{
			--(*curr);
			while (**curr != '/')
				--(*curr);
			if (*curr == root)
				*(*curr + 1) = '\0';
			else
				**curr = '\0';
		}
	}
	else if (start != end && (start[0] != '.' || end != start + 1))
	{
		ft_memcpy(*curr, start - 1, end - start + 1);
		*curr += end - start + 1;
		**curr = '\0';
		if (*end == '/' && (err = sh_check_dir(root)))
			return (err);
	}
	return (0);
}

int			sh_path_canonical(const char *path, char **canon)
{
	const char	*start;
	const char	*end;
	char		*curr;
	int			err;

	FT_ASSERT(path != NULL);
	FT_ASSERT(canon != NULL);
	*canon = NULL;
	if (path[0] != '/')
		return (-1);
	if (!(*canon = ft_strnew(ft_strlen(path))))
		return (SH_ERR_NOMEM);
	ft_strcpy(*canon, "/");
	curr = *canon;
	start = path + 1;
	while (*start && (end = ft_strchrnul(start, '/')))
	{
		if ((err = process_element(*canon, &curr, start, end)))
		{
			ft_memdel((void **)canon);
			return (err);
		}
		start = end[0] == '/' ? end + 1 : end;
	}
	return (0);
}
