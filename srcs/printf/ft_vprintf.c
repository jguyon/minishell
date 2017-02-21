/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 15:40:11 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/13 00:02:32 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_vprintf(const char *format, va_list args)
{
	int		res;

	res = ft_vfprintf(FT_STDOUT, format, args);
	ft_fflush(FT_STDOUT);
	return (res);
}
