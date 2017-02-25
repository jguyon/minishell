/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin_echo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 17:40:52 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/25 01:14:02 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "sh_builtins.h"

static void	test_no_options(t_tap *t)
{
	t_sh_env	env;
	char		*av[] = {"echo", "hello", "world", NULL};
	char		*ep[] = {NULL};

	ft_tap_plan(t, 3);
	if (FT_TAP_OK(t, sh_env_start(&env, ep) == 0))
	{
		FT_TAP_IEQ(t,
			sh_builtin_echo(3, av, &env), 0);
		STDOUT_EQ(t, "hello world\n");
		sh_env_end(&env);
	}
}

static void	test_no_newline(t_tap *t)
{
	t_sh_env	env;
	char		*av[] = {"echo", "-n", "hello", "world", NULL};
	char		*ep[] = {NULL};

	ft_tap_plan(t, 3);
	if (FT_TAP_OK(t, sh_env_start(&env, ep) == 0))
	{
		FT_TAP_IEQ(t,
				   sh_builtin_echo(4, av, &env), 0);
		STDOUT_EQ(t, "hello world");
		sh_env_end(&env);
	}
}

static void	test_no_args(t_tap *t)
{
	t_sh_env	env;
	char		*av[] = {"echo", NULL};
	char		*ep[] = {NULL};

	ft_tap_plan(t, 3);
	if (FT_TAP_OK(t, sh_env_start(&env, ep) == 0))
	{
		FT_TAP_IEQ(t,
				   sh_builtin_echo(1, av, &env), 0);
		STDOUT_EQ(t, "\n");
		sh_env_end(&env);
	}
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_no_options);
	FT_TAP_TEST(t, test_no_newline);
	FT_TAP_TEST(t, test_no_args);
}
