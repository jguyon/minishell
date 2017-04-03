/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tap_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 23:30:58 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/13 22:43:25 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tap.h"
#include <stdio.h>

int		ft_tap_test(t_tap *t, void (*test)(t_tap *s), const char *msg)
{
	t_tap	sub;

	if (!msg)
		msg = "passes";
	printf("%*s# Subtest: %s\n", (int)t->nesting, "", msg);
	sub.nesting = t->nesting + 4;
	sub.plan = 0;
	sub.run = 0;
	sub.passed = 0;
	test(&sub);
	ft_tap_end(&sub);
	if (sub.passed != sub.run)
		ft_tap_fail(t, msg);
	else
		ft_tap_pass(t, msg);
	return (sub.passed == sub.run);
}
