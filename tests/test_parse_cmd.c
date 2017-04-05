/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 22:11:33 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/05 15:59:39 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "sh_parse.h"
#include "ft_memory.h"

static void	del_argv(char **argv)
{
	size_t	i;

	i = 0;
	while (argv[i])
	{
		ft_memdel((void **)&(argv[i]));
		++i;
	}
	ft_memdel((void **)&argv);
}

static void	test_empty(t_tap *t)
{
	t_sh_lexer	lex;
	t_sh_cmd	*cmd;
	t_stream	*stm;
	char		str[] = " \t\n";

	ft_tap_plan(t, 2);
	if ((stm = ft_fmemopen(str, sizeof(str) - 1, "r"))
		&& sh_lexer_init(&lex, stm) == 0)
	{
		FT_TAP_IEQ(t, sh_parse_cmd(&lex, &cmd), 0);
		FT_TAP_OK(t, cmd == NULL);
		sh_cmd_del(&cmd);
	}
	ft_fclose(stm);
}

static void	test_noargs(t_tap *t)
{
	t_sh_lexer	lex;
	t_sh_cmd	*cmd;
	t_stream	*stm;
	char		str[] = "echo";
	char		**argv;

	ft_tap_plan(t, 4);
	if ((stm = ft_fmemopen(str, sizeof(str) - 1, "r"))
		&& sh_lexer_init(&lex, stm) == 0)
	{
		FT_TAP_IEQ(t, sh_parse_cmd(&lex, &cmd), 0);
		if (FT_TAP_OK(t, (argv = sh_cmd_toargv(&cmd)) != NULL))
		{
			FT_TAP_SEQ(t, argv[0], "echo");
			FT_TAP_OK(t, argv[1] == NULL);
			del_argv(argv);
		}
	}
	ft_fclose(stm);
}

static void	test_args(t_tap *t)
{
	t_sh_lexer	lex;
	t_sh_cmd	*cmd;
	t_stream	*stm;
	char		str[] = "echo hello world\n";
	char		**argv;

	ft_tap_plan(t, 6);
	if ((stm = ft_fmemopen(str, sizeof(str) - 1, "r"))
		&& sh_lexer_init(&lex, stm) == 0)
	{
		FT_TAP_IEQ(t, sh_parse_cmd(&lex, &cmd), 0);
		if (FT_TAP_OK(t, (argv = sh_cmd_toargv(&cmd)) != NULL))
		{
			FT_TAP_SEQ(t, argv[0], "echo");
			FT_TAP_SEQ(t, argv[1], "hello");
			FT_TAP_SEQ(t, argv[2], "world");
			FT_TAP_OK(t, argv[3] == NULL);
			del_argv(argv);
		}
	}
	ft_fclose(stm);
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_empty);
	FT_TAP_TEST(t, test_noargs);
	FT_TAP_TEST(t, test_args);
}
