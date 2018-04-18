/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tap_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 23:05:23 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/13 22:45:09 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tap.h"
#include <stdio.h>

void	ft_tap_start(t_tap *t)
{
	t->nesting = 0;
	t->plan = 0;
	t->run = 0;
	t->passed = 0;
	printf("TAP version 13\n");
}