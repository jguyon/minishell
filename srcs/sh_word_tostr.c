/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_word_tostr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 23:10:58 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/24 23:43:25 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_ast.h"
#include "ft_memory.h"

char	*sh_word_tostr(t_sh_word **word)
{
	char	*str;

	if (!(*word))
		return (NULL);
	str = (*word)->str;
	(*word)->str = NULL;
	ft_memdel((void **)word);
	return (str);
}
