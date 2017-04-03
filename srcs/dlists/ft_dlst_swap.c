/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 00:57:12 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 18:18:45 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"
#include "ft_debug.h"

static void	swap_adjacent(t_dlist_node *prev, t_dlist_node *next)
{
	next->next->prev = prev;
	prev->prev->next = next;
	next->prev = prev->prev;
	prev->next = next->next;
	next->next = prev;
	prev->prev = next;
}

static void	swap_separated(t_dlist_node *n1, t_dlist_node *n2)
{
	t_dlist_node	*prev;
	t_dlist_node	*next;

	n1->prev->next = n2;
	n1->next->prev = n2;
	n2->next->prev = n1;
	n2->prev->next = n1;
	prev = n1->prev;
	n1->prev = n2->prev;
	n2->prev = prev;
	next = n1->next;
	n1->next = n2->next;
	n2->next = next;
}

void		ft_dlst_swap(t_dlist_node *n1, t_dlist_node *n2)
{
	FT_ASSERT(n1 != NULL);
	FT_ASSERT(n1->prev && n1->next);
	FT_ASSERT(n2 != NULL);
	FT_ASSERT(n2->prev && n2->next);
	if (n1->next == n2)
		swap_adjacent(n1, n2);
	else if (n1->prev == n2)
		swap_adjacent(n2, n1);
	else if (n1 != n2)
		swap_separated(n1, n2);
}
