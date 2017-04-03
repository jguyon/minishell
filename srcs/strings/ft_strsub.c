/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:34:35 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/17 21:34:59 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_strings.h"

char	*ft_strsub(char const *str, unsigned int start, size_t len)
{
	char	*sub;

	sub = NULL;
	if (str && (sub = ft_strnew(len)))
	{
		ft_memcpy(sub, str + start, len);
		sub[len] = 0;
	}
	return (sub);
}
