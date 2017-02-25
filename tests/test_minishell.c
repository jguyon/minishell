/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 02:48:19 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/25 03:27:19 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "minishell.h"
#include <limits.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

static void	test_parse_cmd(t_tap *t)
{
	t_cmd			*cmd;
	t_stream		*stm;
	char			str[LINE_MAX + 1];
	t_dlist_node	*node;

	ft_tap_plan(t, 12);
	strcpy(str, " \t \t \n");
	if ((stm = ft_fmemopen(str, strlen(str), "r")))
	{
		cmd = ms_parse_cmd(stm);
		FT_TAP_OK(t, cmd == NULL);
		ms_destroy_cmd(&cmd);
		ft_fclose(stm);
	}
	strcpy(str, " \t ls\t \n");
	if ((stm = ft_fmemopen(str, strlen(str), "r")))
	{
		cmd = ms_parse_cmd(stm);
		if (FT_TAP_OK(t, cmd != NULL))
		{
			FT_TAP_SEQ(t, cmd->name, "ls");
			FT_TAP_UEQ(t, cmd->arg_count, 0);
			FT_TAP_OK(t, ft_dlst_empty(&(cmd->args)));
		}
		ms_destroy_cmd(&cmd);
		ft_fclose(stm);
	}
	strcpy(str, "echo hello world");
	if ((stm = ft_fmemopen(str, strlen(str), "r")))
	{
		cmd = ms_parse_cmd(stm);
		if (FT_TAP_OK(t, cmd != NULL))
		{
			FT_TAP_SEQ(t, cmd->name, "echo");
			FT_TAP_UEQ(t, cmd->arg_count, 2);
			FT_TAP_OK(t, (node = ft_dlst_first(&(cmd->args))) != NULL);
			FT_TAP_SEQ(t,
				((t_arg *)FT_DLST_ENTRY(&(cmd->args), node))->str, "hello");
			FT_TAP_OK(t, (node = ft_dlst_last(&(cmd->args))) != NULL);
			FT_TAP_SEQ(t,
				((t_arg *)FT_DLST_ENTRY(&(cmd->args), node))->str, "world");
		}
		ms_destroy_cmd(&cmd);
		ft_fclose(stm);
	}
}

static void	test_exec_cmd(t_tap *t)
{
	t_cmd		*cmd;
	t_stream	*stm;
	char		str[256];
	int			fd;
	t_env		env;
	char		*envp[] = {"PATH=/bin", NULL};

	ft_tap_plan(t, 3);
	if ((fd = creat("/tmp/minishell_test_remove", S_IRWXU) < 0))
		return ;
	close(fd);
	ms_env_start(&env, envp);
	cmd = NULL;
	strcpy(str, "rm /tmp/minishell_test_remove");
	if ((stm = ft_fmemopen(str, strlen(str), "r"))
		&& (cmd = ms_parse_cmd(stm)))
	{
		ms_exec_cmd(cmd, &env);
		FT_TAP_NOTIEQ(t, access("/tmp/minishell_test_remove", F_OK), 0);
		STDERR_EQ(t, "");
	}
	ms_destroy_cmd(&cmd);
	ft_fclose(stm);
	strcpy(str, "non/existing/file arg1 arg2");
	if ((stm = ft_fmemopen(str, strlen(str), "r"))
		&& (cmd = ms_parse_cmd(stm)))
	{
		ms_exec_cmd(cmd, &env);
		STDERR_EQ(t, "minishell: non/existing/file: Not found\n");
	}
	ms_destroy_cmd(&cmd);
	ft_fclose(stm);
	ms_env_end(&env);
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_parse_cmd);
	FT_TAP_TEST(t, test_exec_cmd);
}
