/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 15:36:08 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 16:54:19 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_memory.h"
#include "ft_strings.h"
#include "ft_debug.h"

char	*ft_strdup(const char *str)
{
	char	*dup;
	size_t	len;

	FT_ASSERT(str != NULL);
	len = ft_strlen(str) + 1;
	if (!(dup = (char *)malloc(len * sizeof(*dup))))
		return (NULL);
	return (ft_memcpy(dup, str, len));
}
