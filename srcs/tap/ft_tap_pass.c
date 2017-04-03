/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tap_pass.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 23:16:00 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/13 22:41:54 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tap.h"
#include <stdio.h>

void	ft_tap_pass(t_tap *t, const char *msg)
{
	t->run += 1;
	t->passed += 1;
	if (msg)
		printf("%*sok %zu - %s\n", (int)t->nesting, "", t->run, msg);
	else
		printf("%*sok %zu\n", (int)t->nesting, "", t->run);
}
