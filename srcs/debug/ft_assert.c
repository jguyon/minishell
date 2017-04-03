/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 11:48:19 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 14:11:53 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_debug.h"
#include <stdlib.h>

void	ft_assert(const char *file, int line, const char *expr)
{
	if (expr)
	{
		ft_debug(file, line, "`%s` assertion failed", expr);
		exit(FT_ASSERT_EXIT);
	}
}
