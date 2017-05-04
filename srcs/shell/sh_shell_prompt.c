/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_shell_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 15:48:24 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/06 22:20:22 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_shell.h"
#include "sh_lexer.h"
#include "sh_parse.h"
#include "sh_exec.h"
#include "ft_program.h"
#include "ft_streams.h"
#include "ft_memory.h"
#include "ft_debug.h"

static void	print_prompt(t_sh_env *env)
{
	const char	*prompt;

	if (!(prompt = sh_env_getvar(env, "PS1")))
		prompt = "";
	ft_fputs(prompt, FT_STDOUT);
	ft_fflush(FT_STDOUT);
}

static void	exec_input(t_sh_env *env)
{
	t_sh_lexer		lex;
	t_sh_seqlist	*lst;
	t_err			err;
	t_sh_token		delim;

	if ((err = sh_lexer_init(&lex, FT_STDIN))
		|| (err = sh_parse_seqlist(&lex, &lst, &delim))
		|| (lst && (err = sh_exec_seqlist(env, &lst))))
		ft_error(0, err, NULL);
}

int			sh_shell_prompt(t_sh_env *env)
{
	FT_ASSERT(env != NULL);
	if (sh_env_should_exit(env) || ft_feof(FT_STDIN))
		return (-1);
	FT_DEBUG("shell: print and exec prompt");
	print_prompt(env);
	exec_input(env);
	return (0);
}
