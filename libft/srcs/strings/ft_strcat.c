/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 19:33:22 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 17:24:40 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"
#include "ft_debug.h"

char	*ft_strcat(char *dst, const char *src)
{
	FT_ASSERT(dst != NULL);
	FT_ASSERT(src != NULL);
	ft_strcpy(dst + ft_strlen(dst), src);
	return (dst);
}
