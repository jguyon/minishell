/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 15:42:10 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/14 16:33:50 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "ft_streams.h"

char	g_buff[];

void	stdout_reopen(void)
{
	g_buff[0] = '\0';
	ft_fclose(FT_STDOUT);
	FT_STDOUT = ft_fmemopen(g_buff, sizeof(g_buff), "w");
	ft_setvbuf(FT_STDOUT, NULL, FT_IONBF, 0);
}

int		main(void)
{
	t_tap	t;

	stdout_reopen();
	ft_tap_start(&t);
	run_tests(&t);
	ft_tap_end(&t);
	ft_fclose(FT_STDOUT);
	return (0);
}
