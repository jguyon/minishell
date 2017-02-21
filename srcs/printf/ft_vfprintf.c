/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vfprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 15:50:26 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/08 20:20:13 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "priv/pf_parse.h"
#include "ft_strings.h"

int				ft_vfprintf(t_stream *stream, const char *format, va_list args)
{
	size_t		count;
	int			res;
	char		*next;
	t_pf_info	info;

	if (!format || ft_ferror(stream))
		return (-1);
	count = 0;
	while ((next = ft_strchrnul(format, PF_CONV_PREFIX)))
	{
		count += (res = ft_fwrite(format, 1, next - format, stream));
		if (res != next - format || !(*(format = next)))
			break ;
		if (*(++format) == PF_CONV_PREFIX)
			count += ft_fwrite(format++, 1, 1, stream);
		else if ((format = pf_parse_info(format, &info, count, args)))
			count += (res = pf_convert(stream, &info, args));
		if (res < 0 || !format || ft_ferror(stream))
			break ;
	}
	if (res < 0 || !format || ft_ferror(stream))
		return (-1);
	return (count);
}
