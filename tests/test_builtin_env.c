/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 14:04:34 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/25 02:55:47 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "sh_builtins.h"

static void	test_print(t_tap *t)
{
	char		*ep[] = {"USER=john", "HOME=/home/john", NULL};
	char		*av[] = {"env", "PATH=/bin", "USER=Johnny", NULL};
	t_sh_env	env;

	ft_tap_plan(t, 2);
	if (sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_builtin_env(3, av, &env), 0);
		STDOUT_EQ(t, "USER=Johnny\nHOME=/home/john\nPATH=/bin\n");
		sh_env_end(&env);
	}
}

static void	test_exec(t_tap *t)
{
	char		*ep[] = {"USER=john", NULL};
	char		*av[] = {"env", "echo", "hello", NULL};
	t_sh_env	env;

	ft_tap_plan(t, 2);
	if (sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_builtin_env(3, av, &env), 0);
		STDOUT_EQ(t, "hello\n");
		sh_env_end(&env);
	}
}

static void	test_clear(t_tap *t)
{
	char		*ep[] = {"USER=john", NULL};
	char		*av[] = {"env", "-i", "HOME=/home/john", NULL};
	t_sh_env	env;

	ft_tap_plan(t, 2);
	if (sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_builtin_env(3, av, &env), 0);
		STDOUT_EQ(t, "HOME=/home/john\n");
		sh_env_end(&env);
	}
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_print);
	FT_TAP_TEST(t, test_exec);
	FT_TAP_TEST(t, test_clear);
}
