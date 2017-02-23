/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_strerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 15:58:36 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/23 16:06:03 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_errors.h"
#include <stddef.h>

static char	*g_errors[] = {
	[0] = "unkown error",
	[SH_ERR_NOMEM] = "out of memory",
	[SH_ERR_IO] = "input/output error",
};

char		*sh_strerror(int errnum)
{
	if (errnum < 0 || (size_t)errnum >= sizeof(g_errors) / sizeof(g_errors[0]))
		return (NULL);
	return (g_errors[errnum]);
}
