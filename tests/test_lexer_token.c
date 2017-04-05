/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 13:27:14 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/05 14:35:52 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "sh_lexer.h"
#include "ft_streams.h"
#include <stdlib.h>

static void	test_empty(t_tap *t)
{
	char		in[] = "";
	t_stream	*stm;
	t_sh_lexer	lex;
	t_sh_token	tok;

	stm = ft_fmemopen(in, sizeof(in) - 1, "r");
	FT_TAP_IEQ(t, sh_lexer_init(&lex, stm), 0);
	FT_TAP_IEQ(t, sh_lexer_token(&lex, &tok), 0);
	FT_TAP_IEQ(t, tok.type, SH_TOKEN_EOI);
	ft_fclose(stm);
}

static void	test_whitespace(t_tap *t)
{
	char		in[] = "  \t \t  ";
	t_stream	*stm;
	t_sh_lexer	lex;
	t_sh_token	tok;

	stm = ft_fmemopen(in, sizeof(in) - 1, "r");
	FT_TAP_IEQ(t, sh_lexer_init(&lex, stm), 0);
	FT_TAP_IEQ(t, sh_lexer_token(&lex, &tok), 0);
	FT_TAP_IEQ(t, tok.type, SH_TOKEN_EOI);
	ft_fclose(stm);
}

static void	test_single_word(t_tap *t)
{
	char		in[] = "hello";
	t_stream	*stm;
	t_sh_lexer	lex;
	t_sh_token	tok;

	stm = ft_fmemopen(in, sizeof(in) - 1, "r");
	FT_TAP_IEQ(t, sh_lexer_init(&lex, stm), 0);
	FT_TAP_IEQ(t, sh_lexer_token(&lex, &tok), 0);
	FT_TAP_IEQ(t, tok.type, SH_TOKEN_WORD);
	FT_TAP_SEQ(t, tok.data.word, "hello");
	free(tok.data.word);
	FT_TAP_IEQ(t, sh_lexer_token(&lex, &tok), 0);
	FT_TAP_IEQ(t, tok.type, SH_TOKEN_EOI);
	ft_fclose(stm);
}

static void	test_multiple_words(t_tap *t)
{
	char		in[] = "hello world";
	t_stream	*stm;
	t_sh_lexer	lex;
	t_sh_token	tok;

	stm = ft_fmemopen(in, sizeof(in) - 1, "r");
	FT_TAP_IEQ(t, sh_lexer_init(&lex, stm), 0);
	FT_TAP_IEQ(t, sh_lexer_token(&lex, &tok), 0);
	FT_TAP_IEQ(t, tok.type, SH_TOKEN_WORD);
	FT_TAP_SEQ(t, tok.data.word, "hello");
	free(tok.data.word);
	FT_TAP_IEQ(t, sh_lexer_token(&lex, &tok), 0);
	FT_TAP_IEQ(t, tok.type, SH_TOKEN_WORD);
	FT_TAP_SEQ(t, tok.data.word, "world");
	free(tok.data.word);
	FT_TAP_IEQ(t, sh_lexer_token(&lex, &tok), 0);
	FT_TAP_IEQ(t, tok.type, SH_TOKEN_EOI);
	ft_fclose(stm);
}

static void	test_newline_only(t_tap *t)
{
	char		in[] = "\nhello";
	t_stream	*stm;
	t_sh_lexer	lex;
	t_sh_token	tok;

	stm = ft_fmemopen(in, sizeof(in) - 1, "r");
	FT_TAP_IEQ(t, sh_lexer_init(&lex, stm), 0);
	FT_TAP_IEQ(t, sh_lexer_token(&lex, &tok), 0);
	FT_TAP_IEQ(t, tok.type, SH_TOKEN_EOI);
	ft_fclose(stm);
}

static void	test_newline_after_word(t_tap *t)
{
	char		in[] = "hello\nworld";
	t_stream	*stm;
	t_sh_lexer	lex;
	t_sh_token	tok;

	stm = ft_fmemopen(in, sizeof(in) - 1, "r");
	FT_TAP_IEQ(t, sh_lexer_init(&lex, stm), 0);
	FT_TAP_IEQ(t, sh_lexer_token(&lex, &tok), 0);
	FT_TAP_IEQ(t, tok.type, SH_TOKEN_WORD);
	FT_TAP_SEQ(t, tok.data.word, "hello");
	free(tok.data.word);
	FT_TAP_IEQ(t, sh_lexer_token(&lex, &tok), 0);
	FT_TAP_IEQ(t, tok.type, SH_TOKEN_EOI);
	ft_fclose(stm);
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_empty);
	FT_TAP_TEST(t, test_whitespace);
	FT_TAP_TEST(t, test_single_word);
	FT_TAP_TEST(t, test_multiple_words);
	FT_TAP_TEST(t, test_newline_only);
	FT_TAP_TEST(t, test_newline_after_word);
}
