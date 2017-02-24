/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 23:02:29 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/24 02:04:23 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "sh_env.h"
#include "sh_errors.h"
#include "ft_streams.h"
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

	ft_tap_plan(t, 2);
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

	ft_tap_plan(t, 2);
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

	ft_tap_plan(t, 2);
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

static void	test_find_builtin(t_tap *t)
{
	char			*ep[] = {NULL};
	t_sh_env		env;
	t_sh_builtin	*bt;

	ft_tap_plan(t, 2);
	if (sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_env_builtin(&env, "echo", &bt), 0);
		FT_TAP_OK(t, bt != NULL);
		sh_env_end(&env);
	}
}

static void	test_miss_builtin(t_tap *t)
{
	char			*ep[] = {NULL};
	t_sh_env		env;
	t_sh_builtin	*bt;

	ft_tap_plan(t, 2);
	if (sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_env_builtin(&env, "nonexisting", &bt), SH_ERR_NOTFOUND);
		FT_TAP_OK(t, bt == NULL);
		sh_env_end(&env);
	}
}

static void	test_exec_bin(t_tap *t)
{
	char			*ep[] = {NULL};
	t_sh_env		env;
	char			*av[] = {"prog", NULL};

	ft_tap_plan(t, 2);
	if (sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_env_exec_bin(&env, "/bin/false", av), 1);
		FT_TAP_IEQ(t, sh_env_exec_bin(&env, "/bin/true", av), 0);
		sh_env_end(&env);
	}
}

static int	print(int ac, char *const av[], t_sh_env *env)
{
	(void)ac;
	(void)env;
	if (av[1])
	{
		ft_fputs(av[1], FT_STDOUT);
		return (0);
	}
	return (1);
}

static void	test_exec_builtin(t_tap *t)
{
	char			*ep[] = {NULL};
	t_sh_env		env;
	char			*av[] = {"print", "hello", NULL};
	t_sh_builtin	bt = {"print", &print};

	ft_tap_plan(t, 4);
	if (sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_env_exec_builtin(&env, &bt, av), 0);
		STDOUT_EQ(t, "hello");
		av[1] = NULL;
		FT_TAP_IEQ(t, sh_env_exec_builtin(&env, &bt, av), 1);
		STDOUT_EQ(t, "");
		sh_env_end(&env);
	}
}

static void	test_exec_success(t_tap *t)
{
	char		*ep[] = {"PATH=/bin", NULL};
	t_sh_env	env;
	char		*av[] = {"false", NULL};

	ft_tap_plan(t, 2);
	if (sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_env_exec(&env, av), 0);
		FT_TAP_IEQ(t, sh_env_status(&env), 1);
		sh_env_end(&env);
	}
}

static void	test_exec_failure(t_tap *t)
{
	char		*ep[] = {NULL};
	t_sh_env	env;
	char		*av[] = {"non/existing", NULL};

	ft_tap_plan(t, 2);
	if (sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_env_exec(&env, av), SH_ERR_NOTFOUND);
		FT_TAP_IEQ(t, sh_env_status(&env), SH_EXIT_NOTFOUND);
		sh_env_end(&env);
	}
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_find_envpath_bin);
	FT_TAP_TEST(t, test_miss_envpath_bin);
	FT_TAP_TEST(t, test_perm_envpath_bin);
	FT_TAP_TEST(t, test_find_abspath_bin);
	FT_TAP_TEST(t, test_miss_abspath_bin);
	FT_TAP_TEST(t, test_perm_abspath_bin);

	FT_TAP_TEST(t, test_find_builtin);
	FT_TAP_TEST(t, test_miss_builtin);

	FT_TAP_TEST(t, test_exec_bin);
	FT_TAP_TEST(t, test_exec_builtin);

	FT_TAP_TEST(t, test_exec_success);
	FT_TAP_TEST(t, test_exec_failure);
}
