/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tap_diag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 19:36:07 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/13 22:43:04 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tap.h"
#include <stdio.h>

static void	print_key(t_tap *t, const char *key, const char *val, va_list args)
{
	printf("%*s %s: ", (int)t->nesting, "", key);
	vprintf(val, args);
	printf("\n");
}

void		ft_tap_diag(t_tap *t, va_list parent, ...)
{
	va_list		own;
	const char	*key;
	const char	*val;

	if ((key = va_arg(parent, const char *))
		&& (val = va_arg(parent, const char *)))
	{
		printf("%*s ---\n", (int)t->nesting, "");
		while (key && val)
		{
			print_key(t, key, val, parent);
			key = va_arg(parent, const char *);
			val = va_arg(parent, const char *);
		}
		va_start(own, parent);
		while ((key = va_arg(own, const char *))
			&& (val = va_arg(own, const char *)))
			print_key(t, key, val, own);
		va_end(own);
		printf("%*s ...\n", (int)t->nesting, "");
	}
}
