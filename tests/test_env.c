/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 21:36:14 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/17 00:06:34 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "ms_env.h"

static void	test_env_init(t_tap *t)
{
	char	*envp[] = {"USER=john", "HOST=desktop", NULL};
	t_env	env;

	ft_tap_plan(t, 5);
	if (FT_TAP_IEQ(t, ms_env_start(&env, envp), 0))
	{
		FT_TAP_UEQ(t, env.size, 2);
		FT_TAP_SEQ(t, env.envp[0], "USER=john");
		FT_TAP_SEQ(t, env.envp[1], "HOST=desktop");
		FT_TAP_UEQ(t, (ptrdiff_t)env.envp[2], (ptrdiff_t)NULL);
		ms_env_end(&env);
	}
}

static void	test_env_get(t_tap *t)
{
	char	*envp[] = {"USER=john", "PWD=/home/john", NULL};
	t_env	env;

	ft_tap_plan(t, 3);
	if (FT_TAP_IEQ(t, ms_env_start(&env, envp), 0))
	{
		FT_TAP_SEQ(t, ms_env_get(&env, "PWD"), "/home/john");
		FT_TAP_UEQ(t, (ptrdiff_t)ms_env_get(&env, "NULL"), (ptrdiff_t)NULL);
		ms_env_end(&env);
	}
}

static void	test_env_set(t_tap *t)
{
	char	*envp[] = {"USER=john", "HOST=desktop", NULL};
	t_env	env;

	if (FT_TAP_IEQ(t, ms_env_start(&env, envp), 0))
	{
		FT_TAP_IEQ(t, ms_env_set(&env, "HOST", "laptop"), 0);
		FT_TAP_SEQ(t, env.envp[1], "HOST=laptop");
		FT_TAP_SEQ(t, env.envp[0], "USER=john");
		FT_TAP_UEQ(t, (ptrdiff_t)env.envp[2], (ptrdiff_t)NULL);
		FT_TAP_UEQ(t, env.size, 2);
		FT_TAP_IEQ(t, ms_env_set(&env, "HOME", "/home/john"), 0);
		FT_TAP_SEQ(t, env.envp[2], "HOME=/home/john");
		FT_TAP_UEQ(t, (ptrdiff_t)env.envp[3], (ptrdiff_t)NULL);
		FT_TAP_UEQ(t, env.size, 3);
		ms_env_end(&env);
	}
}

static void	test_env_unset(t_tap *t)
{
	char	*envp[] = {"USER=john", "HOST=desktop", "HOME=/home/john", NULL};
	t_env	env;

	if (FT_TAP_IEQ(t, ms_env_start(&env, envp), 0))
	{
		ms_env_unset(&env, "HOST");
		FT_TAP_SEQ(t, env.envp[0], "USER=john");
		FT_TAP_SEQ(t, env.envp[1], "HOME=/home/john");
		FT_TAP_UEQ(t, (ptrdiff_t)env.envp[2], (ptrdiff_t)NULL);
		FT_TAP_UEQ(t, env.size, 2);
		ms_env_end(&env);
	}
}

static void	test_env_clear(t_tap *t)
{
	char	*envp[] = {"USER=john", "HOST=desktop", "HOME=/home/john", NULL};
	t_env	env;

	if (FT_TAP_IEQ(t, ms_env_start(&env, envp), 0))
	{
		ms_env_clear(&env);
		FT_TAP_UEQ(t, (ptrdiff_t)env.envp[0], (ptrdiff_t)NULL);
		FT_TAP_UEQ(t, env.size, 0);
		ms_env_end(&env);
	}
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_env_init);
	FT_TAP_TEST(t, test_env_get);
	FT_TAP_TEST(t, test_env_set);
	FT_TAP_TEST(t, test_env_unset);
	FT_TAP_TEST(t, test_env_clear);
}
