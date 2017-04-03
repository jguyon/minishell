/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdopen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 18:10:09 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/13 20:27:00 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_streams.h"
#include <unistd.h>

static ssize_t			fd_write(void *fd, const char *buff, size_t size)
{
	int		res;

	res = write(*((int *)fd), buff, size);
	return (res < 0 ? 0 : res);
}

static ssize_t			fd_read(void *fd, char *buff, size_t size)
{
	return (read(*((int *)fd), buff, size));
}

static int				fd_close(void *fd)
{
	return (close(*((int *)fd)) ? FT_EOF : 0);
}

static t_stream_funs	g_fd_funs = {
	.write = &fd_write,
	.read = &fd_read,
	.close = &fd_close,
};

t_stream				*ft_fdopen(int fd, const char *mode)
{
	t_stream	*stm;

	if (fd < 0 || !(stm = ft_fopencookie(NULL, mode, g_fd_funs)))
		return (NULL);
	stm->fd = fd;
	return (stm);
}
