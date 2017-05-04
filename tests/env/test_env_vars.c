/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 17:46:03 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/23 19:22:20 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "sh_env.h"

static void	test_copy(t_tap *t)
{
	char		*ep[] = {"USER=john", "HOME=/home/john", NULL};
	char *const	*cpy;
	t_sh_env	env;

	ft_tap_plan(t, 7);
	if (FT_TAP_IEQ(t, sh_env_start(&env, ep), 0))
	{
		if (FT_TAP_OK(t, (cpy = sh_env_vars(&env)) != NULL))
		{
			FT_TAP_SEQ(t, cpy[0], "USER=john");
			FT_TAP_SEQ(t, sh_env_getvar(&env, "USER"), "john");
			FT_TAP_SEQ(t, cpy[1], "HOME=/home/john");
			FT_TAP_SEQ(t, sh_env_getvar(&env, "HOME"), "/home/john");
			FT_TAP_OK(t, cpy[2] == NULL);
		}
		sh_env_end(&env);
	}
}

static void	test_var_existing(t_tap *t)
{
	char		*ep[] = {"USER=john", "HOME=/home/john", NULL};
	char *const	*cpy;
	t_sh_env	env;

	ft_tap_plan(t, 5);
	if (FT_TAP_IEQ(t, sh_env_start(&env, ep), 0))
	{
		FT_TAP_SEQ(t, sh_env_getvar(&env, "USER"), "john");
		FT_TAP_IEQ(t, sh_env_setvar(&env, "USER", "Johnny"), 0);
		cpy = sh_env_vars(&env);
		FT_TAP_SEQ(t, cpy[0], "USER=Johnny");
		FT_TAP_SEQ(t, sh_env_getvar(&env, "USER"), "Johnny");
		sh_env_end(&env);
	}
}

static void	test_var_nonexisting(t_tap *t)
{
	char		*ep[] = {"USER=john", "HOME=/home/john", NULL};
	char *const	*cpy;
	t_sh_env	env;

	ft_tap_plan(t, 6);
	if (FT_TAP_IEQ(t, sh_env_start(&env, ep), 0))
	{
		FT_TAP_OK(t, sh_env_getvar(&env, "PATH") == NULL);
		FT_TAP_IEQ(t, sh_env_setvar(&env, "PATH", "/bin:/usr/bin"), 0);
		cpy = sh_env_vars(&env);
		FT_TAP_SEQ(t, cpy[2], "PATH=/bin:/usr/bin");
		FT_TAP_OK(t, cpy[3] == NULL);
		FT_TAP_SEQ(t, sh_env_getvar(&env, "PATH"), "/bin:/usr/bin");
		sh_env_end(&env);
	}
}

static void	test_var_setnull(t_tap *t)
{
	char		*ep[] = {"USER=john", "HOME=/home/john", NULL};
	char *const	*cpy;
	t_sh_env	env;

	ft_tap_plan(t, 7);
	if (FT_TAP_IEQ(t, sh_env_start(&env, ep), 0))
	{
		FT_TAP_IEQ(t, sh_env_setvar(&env, "HOME", NULL), 0);
		cpy = sh_env_vars(&env);
		FT_TAP_SEQ(t, cpy[1], "HOME=");
		FT_TAP_SEQ(t, sh_env_getvar(&env, "HOME"), "");
		FT_TAP_IEQ(t, sh_env_setvar(&env, "HOME=/home/jj", NULL), 0);
		cpy = sh_env_vars(&env);
		FT_TAP_SEQ(t, cpy[1], "HOME=/home/jj");
		FT_TAP_SEQ(t, sh_env_getvar(&env, "HOME"), "/home/jj");
		sh_env_end(&env);
	}
}

static void	test_var_unset(t_tap *t)
{
	char		*ep[] = {"USER=john", "HOME=/home/john", NULL};
	char *const	*cpy;
	t_sh_env	env;

	ft_tap_plan(t, 4);
	if (FT_TAP_IEQ(t, sh_env_start(&env, ep), 0))
	{
		sh_env_unsetvar(&env, "USER");
		cpy = sh_env_vars(&env);
		FT_TAP_SEQ(t, cpy[0], "HOME=/home/john");
		FT_TAP_OK(t, cpy[1] == NULL);
		FT_TAP_OK(t, sh_env_getvar(&env, "USER") == NULL);
		sh_env_end(&env);
	}
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_copy);
	FT_TAP_TEST(t, test_var_existing);
	FT_TAP_TEST(t, test_var_nonexisting);
	FT_TAP_TEST(t, test_var_setnull);
	FT_TAP_TEST(t, test_var_unset);
}
