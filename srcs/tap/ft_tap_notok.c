/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tap_notok.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 11:49:53 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/03 11:59:38 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tap.h"

int		ft_tap_notok(t_tap *t, int val, const char *msg, ...)
{
	va_list	args;

	if (!msg)
		msg = "is false";
	if (!val)
		ft_tap_pass(t, msg);
	else
	{
		ft_tap_fail(t, msg);
		va_start(args, msg);
		ft_tap_diag(t, args, "wanted", "false", "found", "true", NULL);
		va_end(args);
	}
	return (!val);
}
