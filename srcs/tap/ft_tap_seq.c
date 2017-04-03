/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tap_seq.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 12:48:02 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/13 22:43:49 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tap.h"
#include <stdlib.h>
#include <string.h>

int		ft_tap_seq(t_tap *t, const char *a, const char *b, const char *msg, ...)
{
	va_list	args;
	int		res;
	char	*wanted;
	char	*found;

	if (!msg)
		msg = "are equal";
	if ((res = strcmp(a, b) == 0))
		ft_tap_pass(t, msg);
	else
	{
		ft_tap_fail(t, msg);
		found = ft_tap_quote(a);
		wanted = ft_tap_quote(b);
		va_start(args, msg);
		ft_tap_diag(t, args,
			"wanted", "%s", wanted, "found", "%s", found, NULL);
		free(found);
		free(wanted);
		va_end(args);
	}
	return (res);
}
