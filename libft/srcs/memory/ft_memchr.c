/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:53:37 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 16:31:56 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_debug.h"

#ifndef FT_MEM_OPT

void	*ft_memchr(const void *str, int c, size_t n)
{
	FT_ASSERT(str != NULL || n == 0);
	c = (unsigned char)c;
	while (n)
	{
		if (*((unsigned char *)str) == c)
			return ((void *)str);
		++str;
		--n;
	}
	return (NULL);
}

#else

void	*ft_memchr(const void *str, int c, size_t n)
{
	t_mem_word	word;

	FT_ASSERT(str != NULL || n == 0);
	c = (unsigned char)c;
	while (FT_MEM_ALIGN(str) && n && *((unsigned char *)str) != c)
	{
		++str;
		--n;
	}
	if (n > FT_MEM_WORDLEN && *((unsigned char *)str) != c)
	{
		word = FT_MEM_WORD(c);
		while (n > FT_MEM_WORDLEN
				&& !FT_MEM_HASZERO(*((t_mem_word *)str) ^ word))
		{
			str += FT_MEM_WORDLEN;
			n -= FT_MEM_WORDLEN;
		}
	}
	while (n && *((unsigned char *)str) != c)
	{
		++str;
		--n;
	}
	return (n ? (void *)str : NULL);
}

#endif
