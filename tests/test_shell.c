/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 16:23:57 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/04 14:12:35 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "sh_shell.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static void	test_prompt_flow(t_tap *t)
{
	char		*ep[] = {"PATH=/bin:/usr/bin", NULL};
	t_sh_env	env;

	ft_tap_plan(t, 11);
	stdin_reopen("echo hello world\nfalse\nexit\n");
	if (FT_TAP_IEQ(t, sh_shell_start(&env, ep), 0))
	{
		STDOUT_EQ(t, "");
		FT_TAP_IEQ(t, sh_shell_prompt(&env), 0);
		STDOUT_EQ(t, "$ hello world\n");
		FT_TAP_IEQ(t, sh_shell_prompt(&env), 0);
		STDOUT_EQ(t, "$ ");
		FT_TAP_IEQ(t, sh_shell_prompt(&env), 0);
		STDOUT_EQ(t, "$ ");
		FT_TAP_IEQ(t, sh_shell_prompt(&env), -1);
		STDOUT_EQ(t, "");
		FT_TAP_IEQ(t, sh_shell_end(&env), 1);
	}
}

static void	test_prompt_eof(t_tap *t)
{
	char		*ep[] = {"PATH=/bin:/usr/bin", NULL};
	t_sh_env	env;

	ft_tap_plan(t, 6);
	stdin_reopen("echo hello world");
	if (FT_TAP_IEQ(t, sh_shell_start(&env, ep), 0))
	{
		FT_TAP_IEQ(t, sh_shell_prompt(&env), 0);
		STDOUT_EQ(t, "$ hello world\n");
		FT_TAP_IEQ(t, sh_shell_prompt(&env), -1);
		STDOUT_EQ(t, "");
		FT_TAP_IEQ(t, sh_shell_end(&env), 0);
	}
}

static void	test_prompt_empty(t_tap *t)
{
	char		*ep[] = {"PATH=/bin:/usr/bin", NULL};
	t_sh_env	env;

	ft_tap_plan(t, 8);
	stdin_reopen("  \nexit\n");
	if (FT_TAP_IEQ(t, sh_shell_start(&env, ep), 0))
	{
		FT_TAP_IEQ(t, sh_shell_prompt(&env), 0);
		STDOUT_EQ(t, "$ ");
		FT_TAP_IEQ(t, sh_shell_prompt(&env), 0);
		STDOUT_EQ(t, "$ ");
		FT_TAP_IEQ(t, sh_shell_prompt(&env), -1);
		STDOUT_EQ(t, "");
		FT_TAP_IEQ(t, sh_shell_end(&env), 0);
	}
}

static void	test_prompt_config(t_tap *t)
{
	char		*ep[] = {"PATH=/bin:/usr/bin", "PS1=%> ", NULL};
	t_sh_env	env;

	ft_tap_plan(t, 8);
	stdin_reopen("setenv PS1 >>\nexit\n");
	if (FT_TAP_IEQ(t, sh_shell_start(&env, ep), 0))
	{
		FT_TAP_IEQ(t, sh_shell_prompt(&env), 0);
		STDOUT_EQ(t, "%> ");
		FT_TAP_IEQ(t, sh_shell_prompt(&env), 0);
		STDOUT_EQ(t, ">>");
		FT_TAP_IEQ(t, sh_shell_prompt(&env), -1);
		STDOUT_EQ(t, "");
		FT_TAP_IEQ(t, sh_shell_end(&env), 0);
	}
}

static void	test_home_default(t_tap *t)
{
	char		*ep[] = {NULL};
	t_sh_env	env;
	char		*pwd;

	ft_tap_plan(t, 7);
	stdin_reopen("exit\n");
	if (FT_TAP_IEQ(t, sh_shell_start(&env, ep), 0))
	{
		FT_TAP_SEQ(t, sh_env_getvar(&env, "HOME"), (pwd = getcwd(NULL, 0)));
		free(pwd);
		FT_TAP_IEQ(t, sh_shell_prompt(&env), 0);
		STDOUT_EQ(t, "$ ");
		FT_TAP_IEQ(t, sh_shell_prompt(&env), -1);
		STDOUT_EQ(t, "");
		FT_TAP_IEQ(t, sh_shell_end(&env), 0);
	}
}

static void	test_pwd_init(t_tap *t)
{

	char		*ep[] = {NULL};
	t_sh_env	env;
	char		pwd[256] = {0};
	char		out[256] = {0};

	ft_tap_plan(t, 9);
	stdin_reopen("pwd\nexit\n");
	getcwd(pwd, sizeof(pwd));
	if (FT_TAP_IEQ(t, sh_shell_start(&env, ep), 0))
	{
		FT_TAP_SEQ(t, sh_env_getvar(&env, "PWD"), pwd);
		FT_TAP_IEQ(t, sh_shell_prompt(&env), 0);
		strcat(out, "$ ");
		strcat(out, pwd);
		strcat(out, "\n");
		STDOUT_EQ(t, out);
		FT_TAP_IEQ(t, sh_shell_prompt(&env), 0);
		STDOUT_EQ(t, "$ ");
		FT_TAP_IEQ(t, sh_shell_prompt(&env), -1);
		STDOUT_EQ(t, "");
		FT_TAP_IEQ(t, sh_shell_end(&env), 0);
	}
}

static void	test_path_default(t_tap *t)
{
	char		*ep[] = {NULL};
	t_sh_env	env;

	ft_tap_plan(t, 7);
	stdin_reopen("exit\n");
	if (FT_TAP_IEQ(t, sh_shell_start(&env, ep), 0))
	{
		FT_TAP_SEQ(t, sh_env_getvar(&env, "PATH"), SH_DEFAULT_PATH);
		FT_TAP_IEQ(t, sh_shell_prompt(&env), 0);
		STDOUT_EQ(t, "$ ");
		FT_TAP_IEQ(t, sh_shell_prompt(&env), -1);
		STDOUT_EQ(t, "");
		FT_TAP_IEQ(t, sh_shell_end(&env), 0);
	}
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_prompt_flow);
	FT_TAP_TEST(t, test_prompt_eof);
	FT_TAP_TEST(t, test_prompt_empty);
	FT_TAP_TEST(t, test_prompt_config);
	FT_TAP_TEST(t, test_home_default);
	FT_TAP_TEST(t, test_pwd_init);
	FT_TAP_TEST(t, test_path_default);
}
