/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 21:48:53 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/19 22:44:37 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_program.h"
#include "ft_printf.h"
#include "ft_strings.h"
#include <unistd.h>

#define DEFAULT_PROGNAME "error"
#define DEFAULT_ERROR "unkown error"
#define SEPARATOR ": "
#define FERROR_DIAGNOSTIC "\nError while outputting error\n"

char		*(*g_ft_strerror)(int errnum) = NULL;

static void	print_error(const char *prog, const char *err,
			const char *format, va_list args)
{
	ft_fflush(FT_STDOUT);
	if (prog)
		ft_fputs(prog, FT_STDERR);
	if (format)
	{
		ft_fputs(SEPARATOR, FT_STDERR);
		ft_vfprintf(FT_STDERR, format, args);
	}
	if (err)
		ft_fprintf(FT_STDERR, SEPARATOR "%s", err);
	ft_fputc('\n', FT_STDERR);
	ft_fflush(FT_STDERR);
}

static char	*errnoop(int errnum)
{
	(void)errnum;
	return (NULL);
}

void		ft_error(int status, int errnum, const char *format, ...)
{
	const char	*progname;
	const char	*error;
	va_list		args;

	if (!g_ft_strerror)
		g_ft_strerror = &errnoop;
	if (!(progname = ft_getprogname()))
		progname = DEFAULT_PROGNAME;
	error = NULL;
	if ((errnum && !(error = g_ft_strerror(errnum))
			&& !(error = g_ft_strerror(0)))
		|| (!format && !errnum && g_ft_strerror && !(error = g_ft_strerror(0))))
		error = DEFAULT_ERROR;
	va_start(args, format);
	print_error(progname, error, format, args);
	va_end(args);
	if (ft_ferror(FT_STDERR))
		write(STDERR_FILENO, FERROR_DIAGNOSTIC, ft_strlen(FERROR_DIAGNOSTIC));
	if (status)
		ft_exit(status);
}
