/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fgets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 21:42:46 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/13 22:02:40 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_streams.h"

char	*ft_fgets(char *s, int size, t_stream *stm)
{
	int		c;
	int		i;

	i = 0;
	while (i < size - 1)
	{
		if ((c = ft_fgetc(stm)) == FT_EOF)
			break ;
		if ((s[i++] = (char)c) == '\n')
			break ;
	}
	if (i < size)
		s[i] = '\0';
	if (ft_ferror(stm) || (i == 0 && ft_feof(stm)))
		return (NULL);
	return (s);
}
