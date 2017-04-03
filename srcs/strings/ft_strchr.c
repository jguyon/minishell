/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 20:13:06 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 17:02:31 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_strings.h"
#include "ft_debug.h"

#ifndef FT_MEM_OPT

char	*ft_strchr(const char *str, int c)
{
	FT_ASSERT(str != NULL);
	c = (char)c;
	while (*str != c)
	{
		if (!(*str))
			return (NULL);
		++str;
	}
	return ((char *)str);
}

#else

char	*ft_strchr(const char *str, int c)
{
	t_mem_word	word;

	FT_ASSERT(str != NULL);
	c = (char)c;
	while (FT_MEM_ALIGN(str))
	{
		if (*str == c)
			return ((char *)str);
		if (!(*str))
			return (NULL);
		++str;
	}
	word = FT_MEM_WORD(c);
	while (!FT_MEM_HASZERO(*((t_mem_word *)str)
							& (*((t_mem_word *)str) ^ word)))
		str += FT_MEM_WORDLEN;
	while (*str != c)
	{
		if (!(*str))
			return (NULL);
		++str;
	}
	return ((char *)str);
}

#endif
