/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 18:09:42 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 16:05:56 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_debug.h"

#ifndef FT_MEM_OPT

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	FT_ASSERT(s1 != NULL || n == 0);
	FT_ASSERT(s2 != NULL || n == 0);
	while (n && *((unsigned char *)s1) == *((unsigned char *)s2))
	{
		++s1;
		++s2;
		--n;
	}
	return (n ? ((int)(*((unsigned char *)s1) - *((unsigned char *)s2))) : 0);
}

#else

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	FT_ASSERT(s1 != NULL || n == 0);
	FT_ASSERT(s2 != NULL || n == 0);
	if (FT_MEM_ALIGN(s1) == FT_MEM_ALIGN(s2))
	{
		while (FT_MEM_ALIGN(s1)
				&& n && *((unsigned char *)s1) == *((unsigned char *)s2))
		{
			++s1;
			++s2;
			--n;
		}
		while (n > FT_MEM_WORDLEN && *((t_mem_word *)s1) == *((t_mem_word *)s2))
		{
			s1 += FT_MEM_WORDLEN;
			s2 += FT_MEM_WORDLEN;
			n -= FT_MEM_WORDLEN;
		}
	}
	while (n && *((unsigned char *)s1) == *((unsigned char *)s2))
	{
		++s1;
		++s2;
		--n;
	}
	return (n ? ((int)(*((unsigned char *)s1) - *((unsigned char *)s2))) : 0);
}

#endif
