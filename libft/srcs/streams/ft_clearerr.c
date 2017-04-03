/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clearerr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 15:04:51 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 19:13:50 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_streams.h"
#include "ft_debug.h"

void	ft_clearerr(t_stream *stm)
{
	FT_ASSERT(stm != NULL);
	stm->flags &= ~FT_IOERR;
	stm->flags &= ~FT_IOEOF;
}
