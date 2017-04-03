/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darr_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 00:35:40 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/20 01:30:49 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_darrays.h"
#include <stdlib.h>

void	ft_darr_clear(t_darray *arr)
{
	free(arr->array);
	arr->array = NULL;
	arr->size = 0;
}
