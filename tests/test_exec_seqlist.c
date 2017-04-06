/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec_seqlist.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 21:17:21 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/06 22:01:35 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "sh_exec.h"
#include <stdlib.h>

static void	test_success(t_tap *t)
{
	char			*envp[] = {"PATH=/bin:/usr/bin", NULL};
	t_sh_seqlist	*lst;
	t_sh_cmd		*cmd;
	t_sh_env		env;

	sh_env_start(&env, envp);
	lst = sh_seqlist_new();
	cmd = sh_cmd_new(sh_word_new(ft_strdup("test")));
	sh_cmd_push(cmd, sh_word_new(ft_strdup("2")));
	sh_cmd_push(cmd, sh_word_new(ft_strdup("-eq")));
	sh_cmd_push(cmd, sh_word_new(ft_strdup("2")));
	sh_seqlist_push(lst, cmd);
	cmd = sh_cmd_new(sh_word_new(ft_strdup("test")));
	sh_cmd_push(cmd, sh_word_new(ft_strdup("2")));
	sh_cmd_push(cmd, sh_word_new(ft_strdup("-eq")));
	sh_cmd_push(cmd, sh_word_new(ft_strdup("3")));
	sh_seqlist_push(lst, cmd);
	FT_TAP_IEQ(t, sh_exec_seqlist(&env, &lst), 0);
	FT_TAP_IEQ(t, sh_env_status(&env), 1);
	sh_env_end(&env);
}

static void	test_failure(t_tap *t)
{
	char			*envp[] = {"PATH=/bin:/usr/bin", NULL};
	t_sh_seqlist	*lst;
	t_sh_cmd		*cmd;
	t_sh_env		env;

	sh_env_start(&env, envp);
	lst = sh_seqlist_new();
	cmd = sh_cmd_new(sh_word_new(ft_strdup("testsssss")));
	sh_cmd_push(cmd, sh_word_new(ft_strdup("2")));
	sh_cmd_push(cmd, sh_word_new(ft_strdup("-eq")));
	sh_cmd_push(cmd, sh_word_new(ft_strdup("2")));
	sh_seqlist_push(lst, cmd);
	cmd = sh_cmd_new(sh_word_new(ft_strdup("test")));
	sh_cmd_push(cmd, sh_word_new(ft_strdup("2")));
	sh_cmd_push(cmd, sh_word_new(ft_strdup("-eq")));
	sh_cmd_push(cmd, sh_word_new(ft_strdup("3")));
	sh_seqlist_push(lst, cmd);
	FT_TAP_IEQ(t, sh_exec_seqlist(&env, &lst), 0);
	FT_TAP_IEQ(t, sh_env_status(&env), 1);
	sh_env_end(&env);
}


void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_success);
	FT_TAP_TEST(t, test_failure);
}
