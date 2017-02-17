/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 19:36:33 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/17 16:09:50 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "ms_errors.h"

static void	test_print_error(t_tap *t)
{
	ms_error(0, MS_ERR_NOTFOUND, NULL);
	STDERR_EQ(t, "minishell: Not found\n");
	ms_error(0, MS_ERR_MAX + 1, NULL);
	STDERR_EQ(t, "minishell: Unkown error\n");
	ms_error(0, 0, "%d", 42);
	STDERR_EQ(t, "minishell: 42\n");
	ms_error(0, MS_ERR_NOTFOUND, "%d", 42);
	STDERR_EQ(t, "minishell: 42: Not found\n");
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_print_error);
}
