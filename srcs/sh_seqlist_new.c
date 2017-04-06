/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_seqlist_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 18:06:52 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/06 18:09:21 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_ast.h"
#include "ft_memory.h"

t_sh_seqlist	*sh_seqlist_new(void)
{
	t_sh_seqlist	*lst;

	if (!(lst = (t_sh_seqlist *)ft_memalloc(sizeof(*lst))))
		return (NULL);
	FT_DLST_INIT(&(lst->cmds), t_sh_cmd, node);
	return (lst);
}
