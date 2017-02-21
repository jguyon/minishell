/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 17:49:44 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/19 15:08:30 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_program.h"
#include "ft_memory.h"

int		ft_cleanup(int status)
{
	size_t	i;

	i = 0;
	while (i < FT_ONEXIT_MAX && g_ft_exit_cb[i].fn)
	{
		g_ft_exit_cb[i].fn(status, g_ft_exit_cb[i].arg);
		ft_bzero(&g_ft_exit_cb[i], sizeof(g_ft_exit_cb[i]));
		++i;
	}
	return (status);
}
