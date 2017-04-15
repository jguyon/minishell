/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pipelist_push.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 16:39:02 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/13 16:40:12 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_ast.h"
#include "ft_debug.h"

void	sh_pipelist_push(t_sh_pipelist *pipe, t_sh_cmd *cmd)
{
	FT_ASSERT(pipe != NULL);
	FT_ASSERT(cmd != NULL);
	ft_dlst_pushr(&(pipe->cmds), &(cmd->node));
}
