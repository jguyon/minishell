/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fflush.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 20:08:55 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/13 13:21:33 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_streams.h"
#include "ft_memory.h"

static int	fflushall(void)
{
	size_t	i;
	int		res;

	i = 0;
	res = 0;
	while (i < FT_FOPEN_MAX)
	{
		if (g_ft_streams[i].flags && ft_fflush(&(g_ft_streams[i])))
			res = FT_EOF;
		++i;
	}
	return (res);
}

int			ft_fflush(t_stream *stm)
{
	size_t	len;
	ssize_t	res;

	if (!stm)
		return (fflushall());
	if (ft_ferror(stm))
		return (FT_EOF);
	if ((stm->flags & FT_IOWR) == 0)
		return (0);
	if (!(stm->curr) || !(stm->write) || (len = stm->curr - stm->buff) == 0)
		return (0);
	if (stm->fd < 0)
		res = stm->write(stm->cookie, stm->buff, len);
	else
		res = stm->write(&(stm->fd), stm->buff, len);
	if (res < 0 || (size_t)res != len)
	{
		stm->flags |= FT_IOERR;
		return (FT_EOF);
	}
	stm->curr = stm->buff;
	return (0);
}
