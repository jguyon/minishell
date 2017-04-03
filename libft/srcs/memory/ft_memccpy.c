/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:50:47 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 16:51:20 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_debug.h"

#ifndef FT_MEM_OPT

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	FT_ASSERT(dst != NULL || n == 0);
	FT_ASSERT(src != NULL || n == 0);
	c = (unsigned char)c;
	while (n && (*((unsigned char *)dst++) = *((unsigned char *)src++)) != c)
		--n;
	return (n ? dst : NULL);
}

#else

static void	to_last_word(void **dst, const void **src, int c, size_t *n)
{
	t_mem_word	word;

	while (FT_MEM_ALIGN(*dst) && *n)
	{
		if ((**((unsigned char **)dst) = **((unsigned char **)src)) == c)
			return ;
		--(*dst);
		--(*src);
		--(*n);
	}
	if (*n > FT_MEM_WORDLEN)
	{
		word = FT_MEM_WORD(c);
		while (*n > FT_MEM_WORDLEN
				&& !FT_MEM_HASZERO(**((t_mem_word **)src) ^ word))
		{
			**((t_mem_word **)dst) = **((t_mem_word **)src);
			*dst += FT_MEM_WORDLEN;
			*src += FT_MEM_WORDLEN;
			*n -= FT_MEM_WORDLEN;
		}
	}
}

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	FT_ASSERT(dst != NULL || n == 0);
	FT_ASSERT(src != NULL || n == 0);
	c = (unsigned char)c;
	if (FT_MEM_ALIGN(src) == FT_MEM_ALIGN(dst))
		to_last_word(&dst, &src, c, &n);
	while (n && (*((unsigned char *)dst++) = *((unsigned char *)src++)) != c)
		--n;
	return (n ? dst : NULL);
}

#endif
