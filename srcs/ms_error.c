/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 19:13:12 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/21 18:08:45 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_errors.h"
#include "ft_printf.h"
#include "ft_program.h"
#include <stddef.h>

static const char	*g_errlist[MS_ERR_MAX + 1] = {
	[0] = "Unkown error",
	[MS_ERR_NOMEM] = "Out of memory",
	[MS_ERR_IO] = "IO error",
	[MS_ERR_NOTFOUND] = "Not found",
	[MS_ERR_PERM] = "Permission denied",
	[MS_ERR_NOEXEC] = "Could not execute",
};

void				ms_error(int status, int errnum, const char *format, ...)
{
	va_list	args;

	ft_fflush(FT_STDOUT);
	ft_fprintf(FT_STDERR, "%s", ft_getprogname());
	if (format)
	{
		ft_fputs(": ", FT_STDERR);
		va_start(args, format);
		ft_vfprintf(FT_STDERR, format, args);
		va_end(args);
	}
	if (errnum > 0)
	{
		ft_fputs(": ", FT_STDERR);
		if (errnum <= MS_ERR_MAX && g_errlist[errnum] != NULL)
			ft_fputs(g_errlist[errnum], FT_STDERR);
		else
			ft_fputs(g_errlist[0], FT_STDERR);
	}
	ft_fputc('\n', FT_STDERR);
	if (status != 0)
		ft_exit(status);
}
