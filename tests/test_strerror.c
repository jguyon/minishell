/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strerror.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 16:07:43 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/23 16:13:32 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "sh_errors.h"
#include <limits.h>

static void test_invalid_errors(t_tap *t)
{
	FT_TAP_OK(t, sh_strerror(-1) == NULL);
	FT_TAP_OK(t, sh_strerror(INT_MAX) == NULL);
}

static void	test_valid_errors(t_tap *t)
{
	FT_TAP_SEQ(t, sh_strerror(SH_ERR_NOMEM), "out of memory");
	FT_TAP_SEQ(t, sh_strerror(0), "unkown error");
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_invalid_errors);
	FT_TAP_TEST(t, test_valid_errors);
}
