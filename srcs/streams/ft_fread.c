/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fread.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 17:02:50 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 19:09:16 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_streams.h"
#include "ft_memory.h"
#include "ft_debug.h"

static size_t	read_nbf(void *mem, size_t size, size_t n, t_stream *stm)
{
	ssize_t	res;
	size_t	bytes;

	bytes = size * n;
	while (bytes)
	{
		if (stm->fd < 0)
			res = stm->read(stm->cookie, mem, size * n);
		else
			res = stm->read(&(stm->fd), mem, size * n);
		if (res < 0)
		{
			stm->flags |= FT_IOERR;
			break ;
		}
		else if (res == 0)
		{
			stm->flags |= FT_IOEOF;
			return (n - bytes / size);
		}
		mem += res;
		bytes -= res;
	}
	return (n);
}

static int		refill(t_stream *stm)
{
	ssize_t	res;
	size_t	size;
	char	*buff;

	size = stm->size;
	buff = stm->buff;
	while (size && !(stm->eof))
	{
		if (stm->fd < 0)
			res = stm->read(stm->cookie, buff, size);
		else
			res = stm->read(&(stm->fd), buff, size);
		if (res < 0)
		{
			stm->flags |= FT_IOERR;
			return (FT_EOF);
		}
		else if (res == 0)
			stm->eof = buff;
		size -= res;
		buff += res;
		stm->curr = stm->buff;
	}
	return (0);
}

static size_t	read_fbf(void *mem, size_t size, size_t n, t_stream *stm)
{
	size_t	bytes;
	size_t	len;

	bytes = n * size;
	while (bytes)
	{
		if (stm->eof == stm->curr)
		{
			stm->flags |= FT_IOEOF;
			return (n - bytes / size);
		}
		else if (stm->eof)
			len = stm->eof - stm->curr;
		else
			len = stm->size - (stm->curr - stm->buff);
		if (bytes < len)
			len = bytes;
		ft_memcpy(mem, stm->curr, len);
		stm->curr += len;
		if (bytes > len && refill(stm) == FT_EOF)
			return (0);
		mem += len;
		bytes -= len;
	}
	return (n);
}

size_t			ft_fread(void *mem, size_t size, size_t n, t_stream *stm)
{
	FT_ASSERT(mem != NULL || n == 0);
	FT_ASSERT(stm != NULL);
	if (size * n == 0 || ft_ferror(stm) || (stm->flags & FT_IORD) == 0)
		return (0);
	if (!(stm->read))
	{
		stm->flags |= FT_EOF;
		return (0);
	}
	if (stm->flags & FT_IONBF)
		return (read_nbf(mem, size, n, stm));
	if (!(stm->buff) && !(stm->buff = (char *)ft_memalloc(stm->size)))
	{
		stm->flags |= FT_IOERR;
		return (0);
	}
	if (!(stm->curr))
		stm->curr = stm->buff + stm->size;
	return (read_fbf(mem, size, n, stm));
}
