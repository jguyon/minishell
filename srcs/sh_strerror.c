/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_strerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 15:58:36 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/27 01:10:55 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_errors.h"
#include <stddef.h>

static char	*g_errors[] = {
	[0] = "unkown error",
	[SH_ERR_NOMEM] = "out of memory",
	[SH_ERR_IO] = "input/output error",
	[SH_ERR_NOTFOUND] = "not found",
	[SH_ERR_NOPERM] = "permission denied",
	[SH_ERR_NOTDIR] = "not a directory",
	[SH_ERR_NOHOME] = "HOME not set",
	[SH_ERR_NOOLDPWD] = "OLDPWD not set",
	[SH_ERR_ARGS2BIG] = "too many arguments",
	[SH_ERR_ARGS2SMALL] = "too few arguments",
	[SH_ERR_BADNUM] = "illegal number",
	[SH_ERR_NOPWD] = "PWD not set",
	[SH_ERR_NOENT] = "no such file or directory",
};

char		*sh_strerror(int errnum)
{
	if (errnum < 0 || (size_t)errnum >= sizeof(g_errors) / sizeof(g_errors[0]))
		return (NULL);
	return (g_errors[errnum]);
}
