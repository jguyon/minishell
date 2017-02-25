/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin_unsetenv.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 19:38:04 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/25 22:47:30 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "sh_builtins.h"

static void	test_non_existing(t_tap *t)
{
	char		*ep[] = {"USER=john", NULL};
	char		*av[] = {"unsetenv", "HOME", NULL};
	t_sh_env	env;

	ft_tap_plan(t, 3);
	if (sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_builtin_unsetenv(2, av, &env), 0);
		FT_TAP_OK(t, sh_env_getvar(&env, "HOME") == NULL);
		FT_TAP_SEQ(t, sh_env_getvar(&env, "USER"), "john");
		sh_env_end(&env);
	}
}

static void	test_existing(t_tap *t)
{
	char		*ep[] = {"USER=john", "HOME=/home/john", NULL};
	char		*av[] = {"unsetenv", "USER", NULL};
	t_sh_env	env;

	ft_tap_plan(t, 3);
	if (sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_builtin_unsetenv(2, av, &env), 0);
		FT_TAP_OK(t, sh_env_getvar(&env, "USER") == NULL);
		FT_TAP_SEQ(t, sh_env_getvar(&env, "HOME"), "/home/john");
		sh_env_end(&env);
	}
}

static void	test_multiple(t_tap *t)
{
	char		*ep[] = {"USER=john", "HOME=/home/john", NULL};
	char		*av[] = {"unsetenv", "USER", "HOME", NULL};
	t_sh_env	env;

	ft_tap_plan(t, 3);
	if (sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_builtin_unsetenv(3, av, &env), 0);
		FT_TAP_OK(t, sh_env_getvar(&env, "USER") == NULL);
		FT_TAP_OK(t, sh_env_getvar(&env, "HOME") == NULL);
		sh_env_end(&env);
	}
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_non_existing);
	FT_TAP_TEST(t, test_existing);
	FT_TAP_TEST(t, test_multiple);
}
