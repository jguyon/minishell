/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darr_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 00:35:40 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 17:43:36 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_darrays.h"
#include "ft_debug.h"
#include <stdlib.h>

void	ft_darr_clear(t_darray *arr)
{
	FT_ASSERT(arr != NULL);
	free(arr->array);
	arr->array = NULL;
	arr->size = 0;
}
