/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:16:45 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 17:19:20 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"
#include "ft_debug.h"

int		ft_strequ(char const *s1, char const *s2)
{
	FT_ASSERT(s1 != NULL);
	FT_ASSERT(s2 != NULL);
	if (ft_strcmp(s1, s2) == 0)
		return (1);
	return (0);
}
