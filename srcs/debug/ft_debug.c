/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 11:48:19 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/03 11:29:53 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_debug.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

static int	debug_fd(const char *path)
{
	static int	fd = -1;

	if (fd < 0)
	{
		if ((fd = open(path, O_WRONLY | O_CREAT | O_TRUNC)) < 0
			|| fchmod(fd, S_IRUSR | S_IWUSR) < 0)
			fd = -1;
	}
	return (fd);
}

void		ft_debug(const char *file, int line, const char *fmt, ...)
{
	va_list		args;
	int			fd;
	const char	*err;

	va_start(args, fmt);
	if ((fd = debug_fd(FT_DEBUG_FILE)) < 0
		|| dprintf(fd, "%s", "debug: ") < 0
		|| vdprintf(fd, fmt, args) < 0
		|| dprintf(fd, " (%s:%d)\n", file, line) < 0)
	{
		err = "debug: could not open " FT_DEBUG_FILE "\n";
		write(FT_DEBUG_FD, err, strlen(err));
	}
	va_end(args);
}
