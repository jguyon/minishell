/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 19:43:04 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 17:25:34 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_strings.h"
#include "ft_debug.h"

char	*ft_strncat(char *dst, const char *src, size_t len)
{
	char	*ret;
	size_t	dlen;

	FT_ASSERT(dst != NULL);
	FT_ASSERT(src != NULL || len == 0);
	ret = dst;
	dlen = ft_strlen(dst);
	dst += dlen;
	if (!ft_memccpy(dst, src, '\0', len))
		dst[len] = '\0';
	return (ret);
}
