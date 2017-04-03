/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:38:31 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 16:57:50 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"
#include "ft_debug.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	head;

	FT_ASSERT(s1 != NULL);
	FT_ASSERT(s2 != NULL);
	join = NULL;
	head = ft_strlen(s1);
	if ((join = ft_strnew(head + ft_strlen(s2))))
	{
		ft_strcpy(join, s1);
		ft_strcpy(join + head, s2);
	}
	return (join);
}
