/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 00:34:52 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/27 18:36:49 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "sh_exec.h"
#include "sh_errors.h"
#include <stdlib.h>

static void	test_success(t_tap *t)
{
	char		*ep[] = {"PATH=/bin:/usr/bin", NULL};
	t_sh_env	env;
	t_sh_cmd	*cmd;
	char		*name;

	ft_tap_plan(t, 3);
	if (sh_env_start(&env, ep) == 0)
	{
		cmd = sh_cmd_new(sh_word_new(ft_strdup("test")));
		sh_cmd_push(cmd, sh_word_new(ft_strdup("2")));
		sh_cmd_push(cmd, sh_word_new(ft_strdup("-eq")));
		sh_cmd_push(cmd, sh_word_new(ft_strdup("1")));
		FT_TAP_IEQ(t, sh_exec_cmd(&env, cmd, &name), 0);
		FT_TAP_SEQ(t, name, "test");
		free(name);
		FT_TAP_IEQ(t, sh_env_status(&env), 1);
		sh_env_end(&env);
	}
}

static void	test_failure(t_tap *t)
{
	char		*ep[] = {NULL};
	t_sh_env	env;
	t_sh_cmd	*cmd;
	char		*name;

	ft_tap_plan(t, 3);
	if (sh_env_start(&env, ep) == 0)
	{
		cmd = sh_cmd_new(sh_word_new(ft_strdup("test")));
		sh_cmd_push(cmd, sh_word_new(ft_strdup("2")));
		sh_cmd_push(cmd, sh_word_new(ft_strdup("-eq")));
		sh_cmd_push(cmd, sh_word_new(ft_strdup("1")));
		FT_TAP_IEQ(t, sh_exec_cmd(&env, cmd, &name), SH_ERR_NOTFOUND);
		FT_TAP_SEQ(t, name, "test");
		free(name);
		FT_TAP_IEQ(t, sh_env_status(&env), SH_EXIT_NOTFOUND);
		sh_env_end(&env);
	}
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_success);
	FT_TAP_TEST(t, test_failure);
}
