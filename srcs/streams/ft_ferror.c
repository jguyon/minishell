/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ferror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 20:06:13 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 19:12:34 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_streams.h"
#include "ft_debug.h"

int		ft_ferror(t_stream *stm)
{
	FT_ASSERT(stm != NULL);
	return (!(stm->flags) || (stm->flags & FT_IOERR) ? FT_EOF : 0);
}
