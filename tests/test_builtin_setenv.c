/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin_setenv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 19:16:03 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/25 02:28:26 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "sh_builtins.h"

static void	test_print(t_tap *t)
{
	char		*ep[] = {"HOME=/home/john", "USER=john", NULL};
	char		*av[] = {"setenv", NULL};
	t_sh_env	env;

	ft_tap_plan(t, 2);
	if (sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_builtin_setenv(1, av, &env), 0);
		STDOUT_EQ(t, "HOME=/home/john\nUSER=john\n");
		sh_env_end(&env);
	}
}

static void	test_empty(t_tap *t)
{
	char		*ep[] = {"HOME=/home/john", "USER=john", NULL};
	char		*av[] = {"setenv", "USER", NULL};
	t_sh_env	env;

	ft_tap_plan(t, 2);
	if (sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_builtin_setenv(2, av, &env), 0);
		FT_TAP_SEQ(t, sh_env_getvar(&env, "USER"), "");
		sh_env_end(&env);
	}
}

static void	test_value(t_tap *t)
{
	char		*ep[] = {"HOME=/home/john", "USER=john", NULL};
	char		*av[] = {"setenv", "USER", "Johnny", NULL};
	t_sh_env	env;

	ft_tap_plan(t, 2);
	if (sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_builtin_setenv(3, av, &env), 0);
		FT_TAP_SEQ(t, sh_env_getvar(&env, "USER"), "Johnny");
		sh_env_end(&env);
	}
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_print);
	FT_TAP_TEST(t, test_empty);
	FT_TAP_TEST(t, test_value);
}
