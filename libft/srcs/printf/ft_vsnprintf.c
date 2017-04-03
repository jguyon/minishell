/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vsnprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 16:02:31 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/14 12:27:42 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_stream_funs	g_noop_funs;

int						ft_vsnprintf(char *str, size_t size,
							const char *format, va_list args)
{
	t_stream	*stm;
	int			count;
	va_list		cpy;

	if (!str && size > 0)
		return (-1);
	if (!(stm = ft_fopencookie(NULL, "w", g_noop_funs)))
		return (-1);
	ft_setvbuf(stm, NULL, FT_IONBF, 0);
	va_copy(cpy, args);
	count = ft_vfprintf(stm, format, cpy);
	va_end(cpy);
	if (ft_fclose(stm) || count < 0)
		return (-1);
	if (!str)
		return (count);
	if (!(stm = ft_fmemopen(str, size, "w")))
		return (-1);
	ft_setvbuf(stm, NULL, FT_IONBF, 0);
	ft_vfprintf(stm, format, args);
	ft_fclose(stm);
	str[(size_t)count >= size ? size - 1 : count] = '\0';
	return (count);
}
