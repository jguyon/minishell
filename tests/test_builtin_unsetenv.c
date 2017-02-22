/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin_unsetenv.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 19:38:04 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/22 19:44:00 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "ms_builtins.h"

static void	test_non_existing(t_tap *t)
{
	char	*ep[] = {"USER=john", NULL};
	char	*av[] = {"unsetenv", "HOME", NULL};
	t_env	env;

	ft_tap_plan(t, 3);
	if (ms_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, ms_builtin_unsetenv(2, av, &env), 0);
		FT_TAP_OK(t, ms_env_get(&env, "HOME") == NULL);
		FT_TAP_SEQ(t, ms_env_get(&env, "USER"), "john");
		ms_env_end(&env);
	}
}

static void	test_existing(t_tap *t)
{
	char	*ep[] = {"USER=john", NULL};
	char	*av[] = {"unsetenv", "USER", NULL};
	t_env	env;

	ft_tap_plan(t, 2);
	if (ms_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, ms_builtin_unsetenv(2, av, &env), 0);
		FT_TAP_OK(t, ms_env_get(&env, "USER") == NULL);
		ms_env_end(&env);
	}
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_non_existing);
	FT_TAP_TEST(t, test_existing);
}
