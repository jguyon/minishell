/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tap_ueq.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 12:14:18 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/03 12:15:03 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tap.h"

int		ft_tap_ueq(t_tap *t, uintmax_t a, uintmax_t b, const char *msg, ...)
{
	va_list	args;

	if (!msg)
		msg = "are equal";
	if (a == b)
		ft_tap_pass(t, msg);
	else
	{
		ft_tap_fail(t, msg);
		va_start(args, msg);
		ft_tap_diag(t, args, "wanted", "%ju", b, "found", "%ju", a, NULL);
		va_end(args);
	}
	return (a == b);
}
