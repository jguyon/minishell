/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tap_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 23:09:15 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/13 22:41:16 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tap.h"
#include <stdio.h>

void	ft_tap_end(t_tap *t)
{
	if (t->plan && t->plan != t->run)
		ft_tap_fail(t, "respects plan");
	else if (t->plan)
		ft_tap_pass(t, "respects plan");
	printf("%*s1..%zu\n", (int)t->nesting, "", t->run);
}
