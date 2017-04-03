/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_shell_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 15:48:24 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/03 18:20:27 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_shell.h"
#include "sh_parse.h"
#include "sh_exec.h"
#include "sh_errors.h"
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
	t_sh_input	input;
	t_sh_cmd	*cmd;
	int			err;
	char		*name;

	name = NULL;
	if ((err = sh_init_input(&input, FT_STDIN))
		|| (err = sh_parse_cmd(&input, &cmd))
		|| (err = sh_exec_cmd(env, cmd, &name)))
	{
		if (err > 0 && name)
			ft_error(0, err, "%s", name);
		else if (err > 0)
			ft_error(0, err, NULL);
	}
	ft_memdel((void **)&name);
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
