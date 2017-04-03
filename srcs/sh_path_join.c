/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_path_join.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 15:38:45 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/03 17:22:01 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_files.h"
#include "sh_errors.h"
#include "ft_strings.h"
#include "ft_memory.h"
#include "ft_debug.h"

int		sh_path_join(const char *parent, const char *child, char **joined)
{
	size_t		parent_len;
	size_t		child_len;

	FT_ASSERT(parent != NULL);
	FT_ASSERT(child != NULL);
	FT_ASSERT(joined != NULL);
	*joined = NULL;
	if (child[0] == '/')
		return (-1);
	child_len = ft_strlen(child);
	if ((parent_len = ft_strlen(parent)) == 0)
	{
		parent = ".";
		parent_len = 1;
	}
	else if (parent[parent_len - 1] == '/')
		--parent_len;
	if (!(*joined = ft_strnew(parent_len + 1 + child_len)))
		return (SH_ERR_NOMEM);
	ft_memcpy(*joined, parent, parent_len);
	(*joined)[parent_len] = '/';
	ft_memcpy(*joined + parent_len + 1, child, child_len);
	return (0);
}
