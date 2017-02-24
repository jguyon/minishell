/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmd_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 20:58:58 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/24 22:20:40 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_ast.h"
#include "ft_memory.h"

static int	del_arg(void *arg, void *acc)
{
	(void)acc;
	ft_dlst_remove(&((t_sh_word *)arg)->node);
	ft_memdel(&arg);
	return (1);
}

void		sh_cmd_del(t_sh_cmd **cmd)
{
	if (*cmd)
	{
		sh_word_del(&((*cmd)->name));
		ft_dlst_foreachl(&((*cmd)->args), NULL, &del_arg);
		ft_memdel((void **)cmd);
	}
}
