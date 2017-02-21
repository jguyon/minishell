/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin_cd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 20:53:39 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/21 22:41:36 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "ms_builtins.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void	test_home(t_tap *t)
{
	char	*ep[] = {"HOME=/tmp/minishell_home", NULL};
	char	*av[] = {"cd", NULL};
	t_env	env;
	char	*oldpwd = NULL;
	char	*newpwd = NULL;
	char	*real = NULL;

	ft_tap_plan(t, 4);
	if ((oldpwd = getcwd(NULL, 0)) && mkdir("/tmp/minishell_home", S_IRWXU) == 0
		&& ms_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, ms_builtin_cd(1, av, &env), 0);
		real = realpath("/tmp/minishell_home", NULL);
		FT_TAP_SEQ(t, (newpwd = getcwd(NULL, 0)), real);
		FT_TAP_SEQ(t, ms_env_get(&env, "PWD"), real);
		FT_TAP_SEQ(t, ms_env_get(&env, "OLDPWD"), oldpwd);
		ms_env_end(&env);
	}
	remove("/tmp/minishell_home");
	chdir(oldpwd);
	free(oldpwd);
	free(newpwd);
	free(real);
}

static void	test_oldpwd(t_tap *t)
{
	char	*ep[] = {"OLDPWD=/tmp/minishell_oldpwd", NULL};
	char	*av[] = {"cd", "-", NULL};
	t_env	env;
	char	*oldpwd = NULL;
	char	*newpwd = NULL;
	char	*real = NULL;

	ft_tap_plan(t, 4);
	if ((oldpwd = getcwd(NULL, 0))
		&& mkdir("/tmp/minishell_oldpwd", S_IRWXU) == 0
		&& ms_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, ms_builtin_cd(2, av, &env), 0);
		real = realpath("/tmp/minishell_oldpwd", NULL);
		FT_TAP_SEQ(t, (newpwd = getcwd(NULL, 0)), real);
		FT_TAP_SEQ(t, ms_env_get(&env, "PWD"), real);
		FT_TAP_SEQ(t, ms_env_get(&env, "OLDPWD"), oldpwd);
		ms_env_end(&env);
	}
	remove("/tmp/minishell_oldpwd");
	chdir(oldpwd);
	free(oldpwd);
	free(newpwd);
	free(real);
}

static void	test_dir(t_tap *t)
{
	char	*ep[] = {NULL};
	char	*av[] = {"cd", "/tmp/minishell_dir", NULL};
	t_env	env;
	char	*oldpwd = NULL;
	char	*newpwd = NULL;
	char	*real = NULL;

	ft_tap_plan(t, 4);
	if ((oldpwd = getcwd(NULL, 0))
		&& mkdir("/tmp/minishell_dir", S_IRWXU) == 0
		&& ms_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, ms_builtin_cd(2, av, &env), 0);
		real = realpath("/tmp/minishell_dir", NULL);
		FT_TAP_SEQ(t, (newpwd = getcwd(NULL, 0)), real);
		FT_TAP_SEQ(t, ms_env_get(&env, "PWD"), real);
		FT_TAP_SEQ(t, ms_env_get(&env, "OLDPWD"), oldpwd);
		ms_env_end(&env);
	}
	remove("/tmp/minishell_dir");
	chdir(oldpwd);
	free(oldpwd);
	free(newpwd);
	free(real);
}

static void	test_error(t_tap *t)
{
	char	*ep[] = {NULL};
	char	*av[] = {"cd", "/non/existent", NULL};
	t_env	env;
	char	*oldpwd = NULL;
	char	*newpwd = NULL;

	ft_tap_plan(t, 3);
	if ((oldpwd = getcwd(NULL, 0)) && ms_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, ms_builtin_cd(2, av, &env), 1);
		FT_TAP_SEQ(t, (newpwd = getcwd(NULL, 0)), oldpwd);
		STDERR_EQ(t, "minishell: cd: No such directory\n");
		ms_env_end(&env);
	}
	chdir(oldpwd);
	free(oldpwd);
	free(newpwd);
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_home);
	FT_TAP_TEST(t, test_oldpwd);
	FT_TAP_TEST(t, test_dir);
	FT_TAP_TEST(t, test_error);
}
