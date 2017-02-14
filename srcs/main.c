/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 15:15:12 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/14 18:29:06 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_program.h"
#include "ft_streams.h"

int		main(void)
{
	ft_fputs("Hello, world!\n", FT_STDOUT);
	return (ft_cleanup(FT_EXIT_SUCCESS));
}
