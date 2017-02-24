/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 22:11:33 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/24 23:41:03 by jguyon           ###   ########.fr       */
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
	t_sh_input	in;
	t_sh_cmd	*cmd;
	t_stream	*stm;
	char		str[] = " \t\n";

	ft_tap_plan(t, 3);
	if ((stm = ft_fmemopen(str, sizeof(str) - 1, "r"))
		&& sh_init_input(&in, stm) == 0)
	{
		FT_TAP_IEQ(t, sh_parse_cmd(&in, &cmd), -1);
		FT_TAP_OK(t, cmd == NULL);
		FT_TAP_IEQ(t, in.next_c, '\n');
		sh_cmd_del(&cmd);
	}
	ft_fclose(stm);
}

static void	test_noargs(t_tap *t)
{
	t_sh_input	in;
	t_sh_cmd	*cmd;
	t_stream	*stm;
	char		str[] = "echo";
	char		**argv;

	ft_tap_plan(t, 5);
	if ((stm = ft_fmemopen(str, sizeof(str) - 1, "r"))
		&& sh_init_input(&in, stm) == 0)
	{
		FT_TAP_IEQ(t, sh_parse_cmd(&in, &cmd), 0);
		if (FT_TAP_OK(t, (argv = sh_cmd_toargv(&cmd)) != NULL))
		{
			FT_TAP_SEQ(t, argv[0], "echo");
			FT_TAP_OK(t, argv[1] == NULL);
			del_argv(argv);
		}
		FT_TAP_IEQ(t, in.next_c, FT_EOF);
	}
	ft_fclose(stm);
}

static void	test_args(t_tap *t)
{
	t_sh_input	in;
	t_sh_cmd	*cmd;
	t_stream	*stm;
	char		str[] = "echo hello world\n";
	char		**argv;

	ft_tap_plan(t, 7);
	if ((stm = ft_fmemopen(str, sizeof(str) - 1, "r"))
		&& sh_init_input(&in, stm) == 0)
	{
		FT_TAP_IEQ(t, sh_parse_cmd(&in, &cmd), 0);
		if (FT_TAP_OK(t, (argv = sh_cmd_toargv(&cmd)) != NULL))
		{
			FT_TAP_SEQ(t, argv[0], "echo");
			FT_TAP_SEQ(t, argv[1], "hello");
			FT_TAP_SEQ(t, argv[2], "world");
			FT_TAP_OK(t, argv[3] == NULL);
			del_argv(argv);
		}
		FT_TAP_IEQ(t, in.next_c, '\n');
	}
	ft_fclose(stm);
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_empty);
	FT_TAP_TEST(t, test_noargs);
	FT_TAP_TEST(t, test_args);
}
