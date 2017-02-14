/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fopencookie.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 19:56:27 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/13 22:09:48 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_streams.h"
#include "ft_strings.h"
#include <unistd.h>

static ssize_t	stdwrite(void *fd, const char *buff, size_t size)
{
	ssize_t	res;

	res = write(*((int *)fd), buff, size);
	return (res < 0 ? 0 : res);
}

static ssize_t	stdread(void *fd, char *buff, size_t size)
{
	return (read(*((int *)fd), buff, size));
}

t_stream		g_ft_streams[FT_FOPEN_MAX] = {
	[0] = {
		.flags = FT_IORD | FT_IONBF,
		.fd = 0,
		.read = &stdread,
	},
	[1] = {
		.flags = FT_IOWR | FT_IOFBF,
		.fd = 1,
		.size = FT_BUFSIZ,
		.write = &stdwrite,
	},
	[2] = {
		.flags = FT_IOWR | FT_IONBF,
		.fd = 2,
		.write = &stdwrite,
	},
};

t_stream		*g_ft_stdin = &(g_ft_streams[0]);
t_stream		*g_ft_stdout = &(g_ft_streams[1]);
t_stream		*g_ft_stderr = &(g_ft_streams[2]);

static t_stream	*next_stream(void)
{
	size_t	i;

	i = 0;
	while (i < FT_FOPEN_MAX && g_ft_streams[i].flags)
		++i;
	if (i >= FT_FOPEN_MAX)
		return (NULL);
	return (&(g_ft_streams[i]));
}

t_stream		*ft_fopencookie(void *cookie, const char *mode,
					t_stream_funs funs)
{
	t_stream	*stream;

	if ((mode[0] != 'w' && mode[0] != 'r') || mode[1] != '\0'
		|| !(stream = next_stream()))
		return (NULL);
	stream->flags = FT_IOFBF;
	stream->flags |= mode[0] == 'r' ? FT_IORD : FT_IOWR;
	stream->fd = -1;
	stream->cookie = cookie;
	stream->write = funs.write;
	stream->read = funs.read;
	stream->close = funs.close;
	stream->size = FT_BUFSIZ;
	stream->curr = NULL;
	stream->eof = NULL;
	stream->buff = NULL;
	return (stream);
}
