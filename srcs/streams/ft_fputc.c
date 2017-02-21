/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fputc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 20:03:38 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/08 18:20:56 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_streams.h"

int		ft_fputc(int c, t_stream *stm)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	if (ft_fwrite(&uc, 1, 1, stm) != 1)
		return (FT_EOF);
	return ((int)uc);
}
