/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fputs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 20:04:47 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/08 18:19:07 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_streams.h"
#include "ft_strings.h"

int		ft_fputs(const char *s, t_stream *stm)
{
	size_t	len;

	len = ft_strlen(s);
	if (ft_fwrite(s, 1, len, stm) != len)
		return (FT_EOF);
	return (0);
}
