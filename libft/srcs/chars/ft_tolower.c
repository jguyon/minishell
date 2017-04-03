/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 23:34:46 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:42:33 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_chars.h"

int		ft_tolower(int c)
{
	return ((c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c);
}
