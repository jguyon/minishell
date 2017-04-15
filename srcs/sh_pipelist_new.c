/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pipelist_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 16:35:59 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/13 16:38:20 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_ast.h"
#include "ft_memory.h"

t_sh_pipelist	*sh_pipelist_new(void)
{
	t_sh_pipelist	*pipe;

	if (!(pipe = (t_sh_pipelist *)ft_memalloc(sizeof(*pipe))))
		return (NULL);
	FT_DLST_INIT(&(pipe->cmds), t_sh_cmd, node);
	return (pipe);
}
