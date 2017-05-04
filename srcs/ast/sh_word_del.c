/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_word_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 20:50:57 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/03 14:58:15 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_ast.h"
#include "ft_memory.h"
#include "ft_debug.h"

void	sh_word_del(t_sh_word **word)
{
	FT_ASSERT(word != NULL);
	if (*word)
	{
		ft_memdel((void **)&((*word)->str));
		ft_memdel((void **)word);
	}
}
