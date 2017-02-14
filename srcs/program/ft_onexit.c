/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_onexit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 17:52:02 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/14 12:39:23 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_program.h"
#include "ft_memory.h"
#include "ft_streams.h"

static void	close_streams(int status, void *arg)
{
	(void)status;
	(void)arg;
	ft_fcloseall();
}

t_exit_cb	g_exit_cb[FT_ONEXIT_MAX] = {
	{ .fn = &close_streams },
};

int			ft_onexit(void (*fn)(int, void *), void *arg)
{
	if (g_exit_cb[FT_ONEXIT_MAX - 1].fn)
		return (-1);
	ft_memmove(&g_exit_cb[1], &g_exit_cb[0],
		sizeof(g_exit_cb) - sizeof(g_exit_cb[0]));
	g_exit_cb[0].arg = arg;
	g_exit_cb[0].fn = fn;
	return (0);
}
