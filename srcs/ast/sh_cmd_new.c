/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmd_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 20:52:28 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/03 15:00:09 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_ast.h"
#include "ft_memory.h"
#include "ft_debug.h"

t_sh_cmd	*sh_cmd_new(t_sh_word *name)
{
	t_sh_cmd	*cmd;

	FT_ASSERT(name != NULL);
	if (!(cmd = (t_sh_cmd *)ft_memalloc(sizeof(*cmd))))
		return (NULL);
	cmd->name = name;
	FT_DLST_INIT(&(cmd->args), t_sh_word, node);
	return (cmd);
}
