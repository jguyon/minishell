/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin_cd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 20:53:39 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/26 21:28:01 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "sh_builtins.h"
#include "ft_strings.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void	test_home(t_tap *t)
{
	char		*ep[] = {"HOME=/tmp/minishell_home", NULL};
	char		*av[] = {"cd", NULL};
	t_sh_env	env;
	char		*oldpwd = NULL;
	char		*newpwd = NULL;
	char		*real = NULL;

	ft_tap_plan(t, 4);
	if ((oldpwd = getcwd(NULL, 0)) && mkdir("/tmp/minishell_home", S_IRWXU) == 0
		&& sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_builtin_cd(1, av, &env), 0);
		real = realpath("/tmp/minishell_home", NULL);
		FT_TAP_SEQ(t, (newpwd = getcwd(NULL, 0)), real);
		FT_TAP_SEQ(t, sh_env_getvar(&env, "PWD"), "/tmp/minishell_home");
		FT_TAP_SEQ(t, sh_env_getvar(&env, "OLDPWD"), oldpwd);
		sh_env_end(&env);
	}
	remove("/tmp/minishell_home");
	chdir(oldpwd);
	free(oldpwd);
	free(newpwd);
	free(real);
}

static void	test_oldpwd(t_tap *t)
{
	char		*ep[] = {"OLDPWD=/tmp/minishell_oldpwd", NULL};
	char		*av[] = {"cd", "-", NULL};
	t_sh_env	env;
	char		*oldpwd = NULL;
	char		*newpwd = NULL;
	char		*real = NULL;

	ft_tap_plan(t, 5);
	if ((oldpwd = getcwd(NULL, 0))
		&& mkdir("/tmp/minishell_oldpwd", S_IRWXU) == 0
		&& sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_builtin_cd(2, av, &env), 0);
		real = realpath("/tmp/minishell_oldpwd", NULL);
		FT_TAP_SEQ(t, (newpwd = getcwd(NULL, 0)), real);
		FT_TAP_SEQ(t, sh_env_getvar(&env, "PWD"), "/tmp/minishell_oldpwd");
		FT_TAP_SEQ(t, sh_env_getvar(&env, "OLDPWD"), oldpwd);
		free(real);
		real = ft_strjoin(newpwd, "\n");
		STDOUT_EQ(t, "/tmp/minishell_oldpwd\n");
		sh_env_end(&env);
	}
	remove("/tmp/minishell_oldpwd");
	chdir(oldpwd);
	free(oldpwd);
	free(newpwd);
	free(real);
}

static void	test_dir(t_tap *t)
{
	char		*ep[] = {NULL};
	char		*av[] = {"cd", "/tmp/minishell_dir", NULL};
	t_sh_env	env;
	char		*oldpwd = NULL;
	char		*newpwd = NULL;
	char		*real = NULL;

	ft_tap_plan(t, 4);
	if ((oldpwd = getcwd(NULL, 0))
		&& mkdir("/tmp/minishell_dir", S_IRWXU) == 0
		&& sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_builtin_cd(2, av, &env), 0);
		real = realpath("/tmp/minishell_dir", NULL);
		FT_TAP_SEQ(t, (newpwd = getcwd(NULL, 0)), real);
		FT_TAP_SEQ(t, sh_env_getvar(&env, "PWD"), "/tmp/minishell_dir");
		FT_TAP_SEQ(t, sh_env_getvar(&env, "OLDPWD"), oldpwd);
		sh_env_end(&env);
	}
	remove("/tmp/minishell_dir");
	chdir(oldpwd);
	free(oldpwd);
	free(newpwd);
	free(real);
}

static void	test_relative(t_tap *t)
{
	char		*ep[] = {"PWD=/tmp/minishell_parent", NULL};
	char		*av[] = {"cd", "../", NULL};
	t_sh_env	env;
	char		*cwd = NULL;
	char		*newpwd = NULL;
	char		*real = NULL;

	cwd = getcwd(NULL, 0);
	mkdir("/tmp/minishell_parent", S_IRWXU);
	chdir("/tmp/minishell_parent");
	ft_tap_plan(t, 4);
	if (sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_builtin_cd(2, av, &env), 0);
		real = realpath("/tmp/", NULL);
		FT_TAP_SEQ(t, (newpwd = getcwd(NULL, 0)), real);
		FT_TAP_SEQ(t, sh_env_getvar(&env, "PWD"), "/tmp");
		FT_TAP_SEQ(t, sh_env_getvar(&env, "OLDPWD"), "/tmp/minishell_parent");
		sh_env_end(&env);
	}
	remove("/tmp/minishell_parent");
	chdir(cwd);
	free(cwd);
	free(newpwd);
	free(real);
}

static void	test_error(t_tap *t)
{
	char		*ep[] = {NULL};
	char		*av[] = {"cd", "/non/existent", NULL};
	t_sh_env	env;
	char		*oldpwd = NULL;
	char		*newpwd = NULL;

	ft_tap_plan(t, 3);
	if ((oldpwd = getcwd(NULL, 0)) && sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_builtin_cd(2, av, &env), 1);
		FT_TAP_SEQ(t, (newpwd = getcwd(NULL, 0)), oldpwd);
		STDERR_EQ(t, "minishell: cd: no such directory\n");
		sh_env_end(&env);
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
	FT_TAP_TEST(t, test_relative);
	FT_TAP_TEST(t, test_error);
}
