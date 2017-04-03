/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tap_ok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 23:24:51 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/03 11:59:53 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tap.h"

int		ft_tap_ok(t_tap *t, int val, const char *msg, ...)
{
	va_list	args;

	if (!msg)
		msg = "is true";
	if (val)
		ft_tap_pass(t, msg);
	else
	{
		ft_tap_fail(t, msg);
		va_start(args, msg);
		ft_tap_diag(t, args, "wanted", "true", "found", "false", NULL);
		va_end(args);
	}
	return (!!val);
}
