/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_hello.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 16:09:37 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/14 16:32:47 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "hello.h"

static void	test_hello(t_tap *t)
{
	hello("42");
	STDOUT_EQ(t, "Hello, 42!\n");
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_hello);
}
