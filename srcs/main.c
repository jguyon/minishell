/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 15:15:12 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/14 15:25:12 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hello.h"
#include "ft_program.h"

int		main(int ac, char **av)
{
	int		i;

	if (ac > 1)
	{
		i = 1;
		while (i < ac)
		{
			hello(av[i]);
			++i;
		}
	}
	else
		hello("you");
	return (ft_cleanup(FT_EXIT_SUCCESS));
}
