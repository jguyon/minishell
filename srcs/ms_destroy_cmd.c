/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_destroy_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 02:26:25 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/17 03:04:49 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_memory.h"
#include "ft_strings.h"

static int	destroy_args(void *entry, void *acc)
{
	(void)acc;
	ft_dlst_remove(&(((t_arg *)entry)->node));
	ft_memdel(&entry);
	return (1);
}

void		ms_destroy_cmd(t_cmd **cmd)
{
	if (*cmd)
	{
		ft_strdel(&((*cmd)->name));
		ft_dlst_foreachl(&((*cmd)->args), NULL, &destroy_args);
		ft_memdel((void **)cmd);
	}
}
