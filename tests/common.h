/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 15:42:46 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/25 16:33:08 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "ft_tap.h"

void	run_tests(t_tap *t);

char	g_inbuff[4096];
void	stdin_reopen(const char *str);

char	g_outbuff[4096];
void	stdout_reopen(void);
# define STDOUT_EQ(t, e) \
	do { \
		ft_tap_seq(t, g_outbuff, e, "stdout == "#e, FT_TAP_DIAG); \
		stdout_reopen(); \
	} while (0)

char	g_errbuff[4096];
void	stderr_reopen(void);
# define STDERR_EQ(t, e)											\
	do {															\
		ft_tap_seq(t, g_errbuff, e, "stderr == "#e, FT_TAP_DIAG);	\
		stderr_reopen();											\
	} while (0)

#endif
