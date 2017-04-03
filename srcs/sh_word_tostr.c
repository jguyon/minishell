/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_word_tostr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 23:10:58 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/03 14:56:59 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_ast.h"
#include "ft_memory.h"
#include "ft_debug.h"

char	*sh_word_tostr(t_sh_word **word)
{
	char	*str;

	FT_ASSERT(word != NULL);
	FT_ASSERT(*word != NULL);
	str = (*word)->str;
	(*word)->str = NULL;
	ft_memdel((void **)word);
	return (str);
}
