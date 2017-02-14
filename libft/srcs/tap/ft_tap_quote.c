/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tap_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 13:56:10 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/13 22:44:34 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tap.h"
#include <stdlib.h>
#include <string.h>

char	*ft_tap_quote(const char *str)
{
	char	*dst;
	char	*ret;

	if (!(dst = (char *)malloc(2 * strlen(str) + 3)))
		return (NULL);
	ret = dst;
	*(dst++) = '"';
	while ((*dst = *(str++)))
	{
		if (*dst == '"')
		{
			*(dst++) = '\\';
			*(dst++) = '"';
		}
		else if (*dst == '\n')
		{
			*(dst++) = '\\';
			*(dst++) = 'n';
		}
		else
			++dst;
	}
	*(dst++) = '"';
	*dst = '\0';
	return (ret);
}
