/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 02:48:19 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/17 03:50:07 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "minishell.h"
#include <limits.h>
#include <string.h>

static void	test_parse_cmd(t_tap *t)
{
	t_cmd			*cmd;
	t_stream		*stm;
	char			str[LINE_MAX + 1];
	t_dlist_node	*node;

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

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_parse_cmd);
}
