/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setvbuf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 17:55:28 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 19:06:20 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_streams.h"
#include "ft_debug.h"

int		ft_setvbuf(t_stream *stm, char *buff, int mode, size_t size)
{
	FT_ASSERT(stm != NULL);
	if (!(stm->flags) || stm->curr
		|| (mode != FT_IONBF && mode != FT_IOFBF)
		|| (mode != FT_IONBF && size == 0))
		return (FT_EOF);
	stm->flags &= ~(FT_IOFBF | FT_IONBF);
	stm->flags |= mode;
	if (stm->flags & FT_IONBF)
	{
		stm->flags &= ~FT_IOUSRBF;
		stm->buff = NULL;
		stm->size = 0;
	}
	else
	{
		if (buff == NULL)
			stm->flags &= ~FT_IOUSRBF;
		else
			stm->flags |= FT_IOUSRBF;
		stm->buff = buff;
		stm->size = size;
	}
	return (0);
}
