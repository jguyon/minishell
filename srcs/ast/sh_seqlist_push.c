/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_seqlist_push.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 18:10:19 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/13 16:46:48 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_ast.h"
#include "ft_debug.h"

void	sh_seqlist_push(t_sh_seqlist *lst, t_sh_pipelist *pipe)
{
	FT_ASSERT(lst != NULL);
	FT_ASSERT(pipe != NULL);
	ft_dlst_pushr(&(lst->pipes), &(pipe->node));
}
