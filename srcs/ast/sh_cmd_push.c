/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmd_push.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 20:56:20 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/03 15:01:02 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_ast.h"
#include "ft_debug.h"

void	sh_cmd_push(t_sh_cmd *cmd, t_sh_word *arg)
{
	FT_ASSERT(cmd != NULL);
	FT_ASSERT(arg != NULL);
	ft_dlst_pushr(&(cmd->args), &(arg->node));
}
