/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_word_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 20:50:57 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/24 22:22:13 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_ast.h"
#include "ft_memory.h"

void	sh_word_del(t_sh_word **word)
{
	if (*word)
	{
		ft_memdel((void **)&((*word)->str));
		ft_memdel((void **)word);
	}
}
