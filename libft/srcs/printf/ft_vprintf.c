/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 15:40:11 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 18:48:42 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_debug.h"

int		ft_vprintf(const char *format, va_list args)
{
	int		res;

	FT_ASSERT(format != NULL);
	res = ft_vfprintf(FT_STDOUT, format, args);
	ft_fflush(FT_STDOUT);
	return (res);
}
