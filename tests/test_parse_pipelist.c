/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_pipelist.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:37:01 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/13 17:54:37 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "sh_parse.h"

static void	test_empty(t_tap *t)
{
	char			in[] = " \t ";
	t_stream		*stm;
	t_sh_lexer		lex;
	t_sh_pipelist	*pipe;
	t_sh_token		delim;

	stm = ft_fmemopen(in, sizeof(in) - 1, "r");
	sh_lexer_init(&lex, stm);
	FT_TAP_IEQ(t, sh_parse_pipelist(&lex, &pipe, &delim), 0);
	FT_TAP_IEQ(t, delim.type, SH_TOKEN_EOI);
	FT_TAP_OK(t, pipe == NULL);
	ft_fclose(stm);
}

static void	test_delim_semi(t_tap *t)
{
	char			in[] = "echo hello world ; ls";
	t_stream		*stm;
	t_sh_lexer		lex;
	t_sh_token		delim;
	t_sh_pipelist	*pipe;
	t_sh_cmd		*cmd;

	stm = ft_fmemopen(in, sizeof(in) - 1, "r");
	sh_lexer_init(&lex, stm);
	FT_TAP_IEQ(t, sh_parse_pipelist(&lex, &pipe, &delim), 0);
	FT_TAP_IEQ(t, delim.type, SH_TOKEN_OPERATOR);
	FT_TAP_IEQ(t, delim.data.operator, SH_OP_SEMI);
	FT_TAP_OK(t, pipe != NULL);
	FT_TAP_OK(t, (cmd = sh_pipelist_pop(pipe)) != NULL);
	FT_TAP_SEQ(t, cmd->name->str, "echo");
	sh_cmd_del(&cmd);
	FT_TAP_OK(t, sh_pipelist_pop(pipe) == NULL);
	sh_pipelist_del(&pipe);
	ft_fclose(stm);
}

static void	test_multiple_commands(t_tap *t)
{
	char			in[] = "echo hello world | cat ; ls";
	t_stream		*stm;
	t_sh_lexer		lex;
	t_sh_token		delim;
	t_sh_pipelist	*pipe;
	t_sh_cmd		*cmd;

	stm = ft_fmemopen(in, sizeof(in) - 1, "r");
	sh_lexer_init(&lex, stm);
	FT_TAP_IEQ(t, sh_parse_pipelist(&lex, &pipe, &delim), 0);
	FT_TAP_IEQ(t, delim.type, SH_TOKEN_OPERATOR);
	FT_TAP_IEQ(t, delim.data.operator, SH_OP_SEMI);
	FT_TAP_OK(t, pipe != NULL);
	FT_TAP_OK(t, (cmd = sh_pipelist_pop(pipe)) != NULL);
	FT_TAP_SEQ(t, cmd->name->str, "echo");
	sh_cmd_del(&cmd);
	FT_TAP_OK(t, (cmd = sh_pipelist_pop(pipe)) != NULL);
	FT_TAP_SEQ(t, cmd->name->str, "cat");
	sh_cmd_del(&cmd);
	FT_TAP_OK(t, sh_pipelist_pop(pipe) == NULL);
	sh_pipelist_del(&pipe);
	ft_fclose(stm);
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_empty);
	FT_TAP_TEST(t, test_delim_semi);
	FT_TAP_TEST(t, test_multiple_commands);
}
