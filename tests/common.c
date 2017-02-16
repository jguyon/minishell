/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 15:42:10 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/16 19:39:09 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "ft_streams.h"
#include "ft_program.h"

char	g_outbuff[];
char	g_errbuff[];

void	stdout_reopen(void)
{
	g_outbuff[0] = '\0';
	ft_fclose(FT_STDOUT);
	FT_STDOUT = ft_fmemopen(g_outbuff, sizeof(g_outbuff), "w");
	ft_setvbuf(FT_STDOUT, NULL, FT_IONBF, 0);
}

void	stderr_reopen(void)
{
	g_errbuff[0] = '\0';
	ft_fclose(FT_STDERR);
	FT_STDOUT = ft_fmemopen(g_errbuff, sizeof(g_errbuff), "w");
	ft_setvbuf(FT_STDERR, NULL, FT_IONBF, 0);
}

int		main(void)
{
	t_tap	t;

	ft_setprogname("minishell");
	stdout_reopen();
	stderr_reopen();
	ft_tap_start(&t);
	run_tests(&t);
	ft_tap_end(&t);
	return (ft_cleanup(0));
}
