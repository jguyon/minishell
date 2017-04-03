/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:48:10 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:50:41 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_memory.h"

void	*ft_memalloc(size_t size)
{
	void	*mem;

	if (!(mem = (unsigned char *)malloc(size)))
		return (NULL);
	ft_bzero(mem, size);
	return (mem);
}
