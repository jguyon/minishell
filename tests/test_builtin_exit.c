/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 03:14:57 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/25 03:20:59 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "sh_builtins.h"

static void	test_no_arg(t_tap *t)
{
	char		*ep[] = {NULL};
	t_sh_env	env;
	char		*av[] = {"exit", NULL};

	ft_tap_plan(t, 2);
	if (sh_env_start(&env, ep) == 0)
	{
		env.exit_status = 3;
		FT_TAP_IEQ(t, sh_builtin_exit(1, av, &env), 3);
		FT_TAP_IEQ(t, env.exit_status, 3);
		sh_env_end(&env);
	}
}

static void	test_num_arg(t_tap *t)
{
	char		*ep[] = {NULL};
	t_sh_env	env;
	char		*av[] = {"exit", "42", NULL};

	ft_tap_plan(t, 2);
	if (sh_env_start(&env, ep) == 0)
	{
		env.exit_status = 3;
		FT_TAP_IEQ(t, sh_builtin_exit(2, av, &env), 42);
		FT_TAP_IEQ(t, env.exit_status, 42);
		sh_env_end(&env);
	}
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_no_arg);
	FT_TAP_TEST(t, test_num_arg);
}
