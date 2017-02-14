/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fclose.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 20:07:40 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/13 13:22:57 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_streams.h"
#include "ft_memory.h"

int		ft_fclose(t_stream *stm)
{
	int		res;

	if (!(stm) || !(stm->flags))
		return (FT_EOF);
	res = 0;
	if (ft_fflush(stm) == FT_EOF)
		res = FT_EOF;
	if ((stm->flags & FT_IOUSRBF) == 0)
		ft_memdel((void **)&(stm->buff));
	if (stm->close
		&& stm->close(stm->fd < 0 ? stm->cookie : &(stm->fd)) == FT_EOF)
		res = FT_EOF;
	stm->flags = 0;
	return (res);
}
