/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 21:45:20 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/04 13:08:50 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_parse.h"
#include "ft_debug.h"

t_err	sh_init_input(t_sh_input *in, t_stream *stm)
{
	FT_ASSERT(in != NULL);
	FT_ASSERT(stm != NULL);
	if (ft_ferror(stm))
		return (SH_ERR_IO);
	in->stm = stm;
	in->next_c = ft_fgetc(stm);
	return (SH_ERR_OK);
}
