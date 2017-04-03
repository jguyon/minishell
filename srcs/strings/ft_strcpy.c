/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 18:42:42 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 17:23:09 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_strings.h"
#include "ft_debug.h"

#ifndef FT_MEM_OPT

char	*ft_strcpy(char *dst, const char *src)
{
	char	*ret;

	FT_ASSERT(dst != NULL);
	FT_ASSERT(src != NULL);
	ret = dst;
	while ((*(dst++) = *(src++)))
		;
	return (ret);
}

#else

char	*ft_strcpy(char *dst, const char *src)
{
	char	*ret;

	FT_ASSERT(dst != NULL);
	FT_ASSERT(src != NULL);
	ret = dst;
	while (FT_MEM_ALIGN(src))
	{
		if (!(*(dst++) = *(src++)))
			return (ret);
	}
	while (!FT_MEM_HASZERO(*((t_mem_word *)src)))
	{
		*((t_mem_word *)dst) = *((t_mem_word *)src);
		src += FT_MEM_WORDLEN;
		dst += FT_MEM_WORDLEN;
	}
	while ((*(dst++) = *(src++)))
		;
	return (ret);
}

#endif
