/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin_cd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 20:53:39 by jguyon            #+#    #+#             */
/*   Updated: 2017/05/04 16:08:32 by jguyon           ###   ########.fr       */
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
	ft_tap_plan(t, 4);
	if (sh_env_start(&env, ep) == 0
		&& sh_env_chdir(&env, "/tmp/minishell_parent", 0) == 0)
	{
		FT_TAP_IEQ(t, sh_builtin_cd(2, av, &env), 0);
		real = realpath("/tmp/", NULL);
		FT_TAP_SEQ(t, (newpwd = getcwd(NULL, 0)), real);
		FT_TAP_SEQ(t, sh_env_getvar(&env, "PWD"), "/tmp");
		FT_TAP_SEQ(t, sh_env_getvar(&env, "OLDPWD"), "/tmp/minishell_parent");
		sh_env_end(&env);
	}
	remove("/tmp/minishell_parent");
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
		STDERR_EQ(t, "minishell: cd: /non/existent: no such file or directory\n");
		sh_env_end(&env);
	}
	free(oldpwd);
	free(newpwd);
}

static void	test_real_path(t_tap *t)
{
	char		*ep[] = {NULL};
	char		*av[] = {"cd", "-P", "/tmp/minishell_link", NULL};
	t_sh_env	env;
	char		*oldpwd = NULL;
	char		*newpwd = NULL;
	char		*real = NULL;

	ft_tap_plan(t, 4);
	mkdir("/tmp/minishell_target", S_IRWXU);
	(void)symlink("/tmp/minishell_target", "/tmp/minishell_link");
	if ((oldpwd = getcwd(NULL, 0)) && sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_builtin_cd(3, av, &env), 0);
		real = realpath("/tmp/minishell_link/", NULL);
		FT_TAP_SEQ(t, (newpwd = getcwd(NULL, 0)), real);
		FT_TAP_SEQ(t, sh_env_getvar(&env, "PWD"), real);
		FT_TAP_SEQ(t, sh_env_getvar(&env, "OLDPWD"), oldpwd);
		sh_env_end(&env);
	}
	remove("/tmp/minishell_link");
	remove("/tmp/minishell_target");
	free(oldpwd);
	free(newpwd);
	free(real);
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_home);
	FT_TAP_TEST(t, test_oldpwd);
	FT_TAP_TEST(t, test_dir);
	FT_TAP_TEST(t, test_relative);
	FT_TAP_TEST(t, test_real_path);
	FT_TAP_TEST(t, test_error);
}
