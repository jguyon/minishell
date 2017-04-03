/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_feof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 18:38:27 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 19:12:55 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_streams.h"
#include "ft_debug.h"

int		ft_feof(t_stream *stm)
{
	FT_ASSERT(stm != NULL);
	return (stm->flags & FT_IOEOF ? FT_EOF : 0);
}
