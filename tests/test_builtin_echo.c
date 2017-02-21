/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin_echo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 17:40:52 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/21 18:04:24 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "ms_builtins.h"
#include "ft_program.h"

static void	test_no_options(t_tap *t)
{
	t_env	env;
	char	*av[] = {"echo", "hello", "world", NULL};
	char	*ep[] = {NULL};

	ft_tap_plan(t, 3);
	if (FT_TAP_OK(t, ms_env_start(&env, ep) == 0))
	{
		FT_TAP_IEQ(t,
			ms_builtin_echo(3, av, &env), FT_EXIT_SUCCESS);
		STDOUT_EQ(t, "hello world\n");
		ms_env_end(&env);
	}
}

static void	test_no_newline(t_tap *t)
{
	t_env	env;
	char	*av[] = {"echo", "-n", "hello", "world", NULL};
	char	*ep[] = {NULL};

	ft_tap_plan(t, 3);
	if (FT_TAP_OK(t, ms_env_start(&env, ep) == 0))
	{
		FT_TAP_IEQ(t,
				   ms_builtin_echo(4, av, &env), FT_EXIT_SUCCESS);
		STDOUT_EQ(t, "hello world");
		ms_env_end(&env);
	}
}

static void	test_no_args(t_tap *t)
{
	t_env	env;
	char	*av[] = {"echo", NULL};
	char	*ep[] = {NULL};

	ft_tap_plan(t, 3);
	if (FT_TAP_OK(t, ms_env_start(&env, ep) == 0))
	{
		FT_TAP_IEQ(t,
				   ms_builtin_echo(1, av, &env), FT_EXIT_SUCCESS);
		STDOUT_EQ(t, "\n");
		ms_env_end(&env);
	}
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_no_options);
	FT_TAP_TEST(t, test_no_newline);
	FT_TAP_TEST(t, test_no_args);
}
