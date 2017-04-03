/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 22:34:19 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 17:17:42 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_strings.h"
#include "ft_debug.h"

#ifndef FT_MEM_OPT

int			ft_strncmp(const char *s1, const char *s2, size_t n)
{
	FT_ASSERT(s1 != NULL || n == 0);
	FT_ASSERT(s2 != NULL || n == 0);
	if (n == 0)
		return (*s1 - *s2);
	while (--n && *s1 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}

#else

static void	to_last_word(const char **s1, const char **s2, size_t *n)
{
	while (*n > FT_MEM_WORDLEN && !FT_MEM_HASZERO(**((t_mem_word **)s1)))
	{
		if (**((t_mem_word **)s1) ^ **((t_mem_word **)s2))
			break ;
		*s1 += FT_MEM_WORDLEN;
		*s2 += FT_MEM_WORDLEN;
		*n -= FT_MEM_WORDLEN;
	}
}

int			ft_strncmp(const char *s1, const char *s2, size_t n)
{
	FT_ASSERT(s1 != NULL || n == 0);
	FT_ASSERT(s2 != NULL || n == 0);
	if (n == 0)
		return (*s1 - *s2);
	if (FT_MEM_ALIGN(s1) == FT_MEM_ALIGN(s2))
	{
		while (FT_MEM_ALIGN(s1))
		{
			if (!n || !(*s1) || *s1 != *s2)
				return (n ? *(unsigned char *)s1 - *(unsigned char *)s2 : 0);
			++s1;
			++s2;
			--n;
		}
		to_last_word(&s1, &s2, &n);
	}
	while (--n && *s1 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return (*((unsigned char *)s1) - *((unsigned char *)s2));
}

#endif
