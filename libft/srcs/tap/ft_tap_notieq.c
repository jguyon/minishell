/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tap_notieq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 11:56:30 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/03 12:04:43 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tap.h"

int		ft_tap_notieq(t_tap *t, intmax_t a, intmax_t b, const char *msg, ...)
{
	va_list	args;

	if (!msg)
		msg = "are not equal";
	if (a != b)
		ft_tap_pass(t, msg);
	else
	{
		ft_tap_fail(t, msg);
		va_start(args, msg);
		ft_tap_diag(t, args, "doNotWant", "%jd", b, "found", "%jd", a, NULL);
		va_end(args);
	}
	return (a != b);
}
