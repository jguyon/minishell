/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clearerr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 15:04:51 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/13 18:41:26 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_streams.h"

void	ft_clearerr(t_stream *stream)
{
	stream->flags &= ~FT_IOERR;
	stream->flags &= ~FT_IOEOF;
}
