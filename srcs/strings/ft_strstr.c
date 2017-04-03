/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 20:38:34 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 17:06:40 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"
#include "ft_debug.h"

char	*ft_strstr(const char *big, const char *little)
{
	const char	*str;
	const char	*cmp;

	FT_ASSERT(big != NULL);
	FT_ASSERT(little != NULL);
	if (!(*little))
		return ((char *)big);
	while (*big)
	{
		str = big;
		cmp = little;
		while (*cmp && *str == *cmp)
		{
			++str;
			++cmp;
		}
		if (!(*cmp))
			return ((char *)big);
		++big;
	}
	return (NULL);
}
