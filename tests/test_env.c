/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 21:36:14 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/18 17:32:48 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "ms_env.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

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
		FT_TAP_OK(t, env.envp[2] == NULL);
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
		FT_TAP_OK(t, ms_env_get(&env, "NULL") == NULL);
		ms_env_end(&env);
	}
}

static void	test_env_set(t_tap *t)
{
	char	*envp[] = {"USER=john", "HOST=desktop", NULL};
	t_env	env;

	ft_tap_plan(t, 10);
	if (FT_TAP_IEQ(t, ms_env_start(&env, envp), 0))
	{
		FT_TAP_IEQ(t, ms_env_set(&env, "HOST", "laptop"), 0);
		FT_TAP_SEQ(t, env.envp[1], "HOST=laptop");
		FT_TAP_SEQ(t, env.envp[0], "USER=john");
		FT_TAP_OK(t, env.envp[2] == NULL);
		FT_TAP_UEQ(t, env.size, 2);
		FT_TAP_IEQ(t, ms_env_set(&env, "HOME", "/home/john"), 0);
		FT_TAP_SEQ(t, env.envp[2], "HOME=/home/john");
		FT_TAP_OK(t, env.envp[3] == NULL);
		FT_TAP_UEQ(t, env.size, 3);
		ms_env_end(&env);
	}
}

static void	test_env_unset(t_tap *t)
{
	char	*envp[] = {"USER=john", "HOST=desktop", "HOME=/home/john", NULL};
	t_env	env;

	ft_tap_plan(t, 9);
	if (FT_TAP_IEQ(t, ms_env_start(&env, envp), 0))
	{
		ms_env_unset(&env, "HOST");
		FT_TAP_SEQ(t, env.envp[0], "USER=john");
		FT_TAP_SEQ(t, env.envp[1], "HOME=/home/john");
		FT_TAP_OK(t, env.envp[2] == NULL);
		FT_TAP_UEQ(t, env.size, 2);
		ms_env_unset(&env, "NULL");
		FT_TAP_SEQ(t, env.envp[0], "USER=john");
		FT_TAP_SEQ(t, env.envp[1], "HOME=/home/john");
		FT_TAP_OK(t, env.envp[2] == NULL);
		FT_TAP_UEQ(t, env.size, 2);
		ms_env_end(&env);
	}
}

static void	test_env_clear(t_tap *t)
{
	char	*envp[] = {"USER=john", "HOST=desktop", "HOME=/home/john", NULL};
	t_env	env;

	ft_tap_plan(t, 3);
	if (FT_TAP_IEQ(t, ms_env_start(&env, envp), 0))
	{
		ms_env_clear(&env);
		FT_TAP_OK(t, env.envp[0] == NULL);
		FT_TAP_UEQ(t, env.size, 0);
		ms_env_end(&env);
	}
}

static void	test_resolve_bin(t_tap *t)
{
	char	*envp[] = {"PATH=.:/tmp", NULL};
	t_env	env;
	int		fd;
	char	*path;

	if ((fd = creat("/tmp/minishell_test_bin", S_IRWXU)) > 0
		&& FT_TAP_IEQ(t, ms_env_start(&env, envp), 0))
	{
		FT_TAP_SEQ(t, path = ms_resolve_path(&env, "minishell_test_bin"),
			"/tmp/minishell_test_bin");
		free(path);
		FT_TAP_OK(t, ms_resolve_path(&env, "non-existing-minishell-bin") == NULL);
		FT_TAP_SEQ(t, path = ms_resolve_path(&env, "minishell_test_bin"),
			"/tmp/minishell_test_bin");
		free(path);
		ms_env_set(&env, "PATH", ":.:");
		FT_TAP_OK(t, ms_resolve_path(&env, "minishell_test_bin") == NULL);
		ms_env_set(&env, "PATH", ".:/tmp");
		FT_TAP_SEQ(t, path = ms_resolve_path(&env, "minishell_test_bin"),
			"/tmp/minishell_test_bin");
		free(path);
		close(fd);
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
	FT_TAP_TEST(t, test_resolve_bin);
}
