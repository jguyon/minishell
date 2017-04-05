/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 21:37:23 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/05 15:57:54 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "sh_parse.h"

static void	test_empty(t_tap *t)
{
	t_sh_lexer	lex;
	t_sh_word	*word;
	t_stream	*stm;
	char		str[] = "  \t";

	ft_tap_plan(t, 2);
	if ((stm = ft_fmemopen(str, sizeof(str) - 1, "r"))
		&& sh_lexer_init(&lex, stm) == 0)
	{
		FT_TAP_IEQ(t, sh_parse_word(&lex, &word), 0);
		FT_TAP_OK(t, word == NULL);
		sh_word_del(&word);
	}
	ft_fclose(stm);
}

static void	test_eof(t_tap *t)
{
	t_sh_lexer	lex;
	t_sh_word	*word;
	t_stream	*stm;
	char		str[] = "  \thello";

	ft_tap_plan(t, 2);
	if ((stm = ft_fmemopen(str, sizeof(str) - 1, "r"))
		&& sh_lexer_init(&lex, stm) == 0)
	{
		FT_TAP_IEQ(t, sh_parse_word(&lex, &word), 0);
		FT_TAP_SEQ(t, word->str, "hello");
		sh_word_del(&word);
	}
	ft_fclose(stm);
}

static void	test_newline(t_tap *t)
{
	t_sh_lexer	lex;
	t_sh_word	*word;
	t_stream	*stm;
	char		str[] = "  \thello\n";

	ft_tap_plan(t, 2);
	if ((stm = ft_fmemopen(str, sizeof(str) - 1, "r"))
		&& sh_lexer_init(&lex, stm) == 0)
	{
		FT_TAP_IEQ(t, sh_parse_word(&lex, &word), 0);
		FT_TAP_SEQ(t, word->str, "hello");
		sh_word_del(&word);
	}
	ft_fclose(stm);
}

static void	test_whitespace(t_tap *t)
{
	t_sh_lexer	lex;
	t_sh_word	*word;
	t_stream	*stm;
	char		str[] = "  \thello \t";

	ft_tap_plan(t, 2);
	if ((stm = ft_fmemopen(str, sizeof(str) - 1, "r"))
		&& sh_lexer_init(&lex, stm) == 0)
	{
		FT_TAP_IEQ(t, sh_parse_word(&lex, &word), 0);
		FT_TAP_SEQ(t, word->str, "hello");
		sh_word_del(&word);
	}
	ft_fclose(stm);
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_empty);
	FT_TAP_TEST(t, test_eof);
	FT_TAP_TEST(t, test_newline);
	FT_TAP_TEST(t, test_whitespace);
}
