/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_shell_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 15:48:24 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/25 22:07:34 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_shell.h"
#include "sh_parse.h"
#include "sh_exec.h"
#include "ft_program.h"
#include "ft_streams.h"

int		sh_shell_prompt(t_sh_env *env)
{
	const char	*prompt;
	t_sh_input	input;
	t_sh_cmd	*cmd;
	int			err;

	if (sh_env_should_exit(env) || ft_feof(FT_STDIN))
		return (-1);
	if (!(prompt = sh_env_getvar(env, "PS1")))
		prompt = "";
	ft_fputs(prompt, FT_STDOUT);
	ft_fflush(FT_STDOUT);
	cmd = NULL;
	if ((err = sh_init_input(&input, FT_STDIN))
		|| (err = sh_parse_cmd(&input, &cmd))
		|| (err = sh_exec_cmd(env, cmd)))
	{
		if (err > 0)
			ft_error(0, err, NULL);
	}
	return (0);
}
