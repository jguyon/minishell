/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 15:42:46 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/14 16:09:05 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "ft_tap.h"

void	run_tests(t_tap *t);

char	g_buff[4096];
void	stdout_reopen(void);
# define STDOUT_EQ(t, e) \
	do { \
		ft_tap_seq(t, g_buff, e, "stdout == "#e, FT_TAP_DIAG); \
		stdout_reopen(); \
	} while (0)

#endif
