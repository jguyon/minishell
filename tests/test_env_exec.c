/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 23:02:29 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/23 23:58:05 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "sh_env.h"
#include "sh_errors.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static void	test_find_envpath_bin(t_tap *t)
{
	char		*ep[] = {"PATH=/non/existing/:/tmp", NULL};
	t_sh_env	env;
	int			binfd;
	char		*binpath = NULL;

	ft_tap_plan(t, 2);
	if ((binfd = creat("/tmp/sh_bin", S_IRWXU)) > 0
		&& sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_env_binpath(&env, "sh_bin", &binpath), 0);
		FT_TAP_SEQ(t, binpath, "/tmp/sh_bin");
		free(binpath);
		sh_env_end(&env);
	}
	close(binfd);
	unlink("/tmp/sh_bin");
}

static void	test_find_abspath_bin(t_tap *t)
{
	char		*ep[] = {"PATH=/non/existing/:/tmp", NULL};
	t_sh_env	env;
	int			binfd;
	char		*binpath = NULL;

	ft_tap_plan(t, 2);
	if ((binfd = creat("/tmp/sh_cur_bin", S_IRWXU)) > 0
		&& sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_env_binpath(&env, "/tmp/sh_cur_bin", &binpath), 0);
		FT_TAP_SEQ(t, binpath, "/tmp/sh_cur_bin");
		free(binpath);
		sh_env_end(&env);
	}
	close(binfd);
	unlink("/tmp/sh_cur_bin");
}

static void	test_miss_envpath_bin(t_tap *t)
{
	char		*ep[] = {"PATH=/non/existing/:/tmp", NULL};
	t_sh_env	env;
	char		*binpath = NULL;

	if (sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_env_binpath(&env, "sh_non_existing", &binpath),
			SH_ERR_NOTFOUND);
		FT_TAP_OK(t, binpath == NULL);
		sh_env_end(&env);
	}
}

static void	test_miss_abspath_bin(t_tap *t)
{
	char		*ep[] = {"PATH=/non/existing/:/tmp", NULL};
	t_sh_env	env;
	char		*binpath = NULL;

	ft_tap_plan(t, 2);
	if (sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_env_binpath(&env, "non/existing/sh", &binpath),
			SH_ERR_NOTFOUND);
		FT_TAP_OK(t, binpath == NULL);
		free(binpath);
		sh_env_end(&env);
	}
}

static void	test_perm_envpath_bin(t_tap *t)
{
	char		*ep[] = {"PATH=/non/existing/:/tmp", NULL};
	t_sh_env	env;
	int			binfd;
	char		*binpath = NULL;

	if ((binfd = creat("/tmp/sh_noperm_bin", 0))
		&& sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_env_binpath(&env, "sh_noperm_bin", &binpath),
			SH_ERR_NOPERM);
		FT_TAP_OK(t, binpath == NULL);
		sh_env_end(&env);
	}
	close(binfd);
	unlink("/tmp/sh_noperm_bin");
}

static void	test_perm_abspath_bin(t_tap *t)
{
	char		*ep[] = {"PATH=/non/existing/:/tmp", NULL};
	t_sh_env	env;
	int			binfd;
	char		*binpath = NULL;

	if ((binfd = creat("/tmp/sh_noperm_bin", 0))
		&& sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_env_binpath(&env, "/tmp/sh_noperm_bin", &binpath),
				   SH_ERR_NOPERM);
		FT_TAP_OK(t, binpath == NULL);
		sh_env_end(&env);
	}
	close(binfd);
	unlink("/tmp/sh_noperm_bin");
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_find_envpath_bin);
	FT_TAP_TEST(t, test_miss_envpath_bin);
	FT_TAP_TEST(t, test_perm_envpath_bin);
	FT_TAP_TEST(t, test_find_abspath_bin);
	FT_TAP_TEST(t, test_miss_abspath_bin);
	FT_TAP_TEST(t, test_perm_abspath_bin);
}
