/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_word_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 20:49:21 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/24 20:50:43 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_ast.h"
#include "ft_memory.h"

t_sh_word	*sh_word_new(char *str)
{
	t_sh_word	*word;

	if (!(word = (t_sh_word *)ft_memalloc(sizeof(*word))))
		return (NULL);
	word->str = str;
	return (word);
}
