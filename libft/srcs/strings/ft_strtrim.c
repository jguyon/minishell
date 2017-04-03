/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:46:27 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 16:58:29 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"
#include "ft_debug.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

char		*ft_strtrim(char const *str)
{
	unsigned int	start;
	size_t			len;

	FT_ASSERT(str != NULL);
	if (!str)
		return (NULL);
	start = 0;
	while (is_space(str[start]))
		++start;
	len = ft_strlen(str + start);
	while (len > 0 && is_space(str[start + len - 1]))
		--len;
	return (ft_strsub(str, start, len));
}
