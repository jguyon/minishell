/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fputs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 20:04:47 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 19:10:26 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_streams.h"
#include "ft_strings.h"
#include "ft_debug.h"

int		ft_fputs(const char *s, t_stream *stm)
{
	size_t	len;

	FT_ASSERT(s != NULL);
	len = ft_strlen(s);
	if (ft_fwrite(s, 1, len, stm) != len)
		return (FT_EOF);
	return (0);
}
