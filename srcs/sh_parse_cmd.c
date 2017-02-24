/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parse_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 19:39:08 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/24 22:19:37 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_parse.h"
#include "sh_errors.h"

int			sh_parse_cmd(t_sh_input *in, t_sh_cmd **cmd)
{
	t_sh_word	*name;
	int			err;

	*cmd = NULL;
	if ((err = sh_parse_word(in, &name)) != 0)
		return (err);
	if (!(*cmd = sh_cmd_new(name)))
	{
		sh_word_del(&name);
		return (SH_ERR_NOMEM);
	}
	while ((err = sh_parse_word(in, &name)) == 0)
		sh_cmd_push(*cmd, name);
	if (err > 0)
	{
		sh_cmd_del(cmd);
		return (err);
	}
	return (0);
}
