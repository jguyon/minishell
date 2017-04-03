/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fcloseall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 02:29:09 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/13 13:23:09 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_streams.h"

int		ft_fcloseall(void)
{
	size_t	i;
	int		res;

	res = 0;
	i = 0;
	while (i < FT_FOPEN_MAX)
	{
		if (g_ft_streams[i].flags && ft_fclose(&(g_ft_streams[i])))
			res = FT_EOF;
		++i;
	}
	return (res);
}
