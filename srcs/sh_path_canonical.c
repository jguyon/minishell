/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_path_nodots.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 16:16:42 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/26 18:57:58 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_files.h"
#include "sh_errors.h"
#include "ft_strings.h"
#include "ft_memory.h"

static char	*process_element(char *root, char *curr,
				const char *start, const char *end)
{
	if (start[0] == '.' && start[1] == '.' && end == start + 2)
	{
		if (curr != root + 1)
		{
			--curr;
			while (*(curr - 1) != '/')
				--curr;
		}
	}
	else if (start != end && (start[0] != '.' || end != start + 1))
	{
		ft_memcpy(curr, start, end - start + 1);
		curr += end - start + 1;
	}
	return (curr);
}

static void	finish_dir(char *root, char *end)
{
	if (end > root + 1 && *(end - 1) == '/')
		*(end - 1) = '\0';
	else
		*end = '\0';
}

int			sh_path_canonical(const char *path, char **canon)
{
	const char	*start;
	const char	*end;
	char		*curr;

	*canon = NULL;
	if (path[0] != '/')
		return (-1);
	if (!(*canon = ft_strnew(ft_strlen(path))))
		return (SH_ERR_NOMEM);
	**canon = '/';
	curr = *canon + 1;
	start = path + 1;
	while (*start && (end = ft_strchrnul(start, '/')))
	{
		curr = process_element(*canon, curr, start, end);
		start = end[0] == '/' ? end + 1 : end;
	}
	finish_dir(*canon, curr);
	return (0);
}
