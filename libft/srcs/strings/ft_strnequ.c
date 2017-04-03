/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:18:29 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 17:20:32 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"
#include "ft_debug.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	FT_ASSERT(s1 != NULL || n == 0);
	FT_ASSERT(s2 != NULL || n == 0);
	if (s1 && s2 && ft_strncmp(s1, s2, n) == 0)
		return (1);
	return (0);
}
