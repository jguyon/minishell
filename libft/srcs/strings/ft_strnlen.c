/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 16:17:56 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 17:01:49 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_strings.h"
#include "ft_debug.h"

#ifndef FT_MEM_OPT

size_t	ft_strnlen(const char *str, size_t max)
{
	const char	*end;

	FT_ASSERT(str != NULL);
	end = str;
	while (*end && (size_t)(end - str) < max)
		++end;
	return (end - str);
}

#else

size_t	ft_strnlen(const char *str, size_t max)
{
	const char	*end;

	FT_ASSERT(str != NULL);
	end = str;
	while (FT_MEM_ALIGN(str) && (size_t)(end - str) < max)
	{
		if (!(*end))
			return (end - str);
		++end;
	}
	while (!FT_MEM_HASZERO(*((t_mem_word *)end))
			&& (size_t)(end - str + FT_MEM_WORDLEN) <= max)
		end += FT_MEM_WORDLEN;
	while (*end && (size_t)(end - str) < max)
		++end;
	return (end - str);
}

#endif
