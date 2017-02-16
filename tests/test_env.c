/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 21:36:14 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/16 22:27:19 by jguyon           ###   ########.fr       */
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
	char	*envp[] = {"USER=john", "HOST=desktop", NULL};
	t_env	env;

	ft_tap_plan(t, 3);
	if (FT_TAP_IEQ(t, ms_env_start(&env, envp), 0))
	{
		FT_TAP_SEQ(t, ms_env_get(&env, "HOST"), "desktop");
		FT_TAP_UEQ(t, (ptrdiff_t)ms_env_get(&env, "NULL"), (ptrdiff_t)NULL);
		ms_env_end(&env);
	}
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_env_init);
	FT_TAP_TEST(t, test_env_get);
}
