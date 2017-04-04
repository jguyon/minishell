/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parse_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:37:19 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/04 11:36:26 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_parse.h"
#include "sh_errors.h"
#include "ft_strings.h"
#include "ft_darrays.h"
#include "ft_debug.h"

static int		skip_whitespace(t_sh_input *in)
{
	while (ft_strchr(SH_WHITESPACE, in->next_c))
		in->next_c = ft_fgetc(in->stm);
	if (in->next_c == FT_EOF || in->next_c == SH_NEWLINE)
		return (-1);
	return (0);
}

static t_err	read_word(t_sh_input *in, t_darray *dstr)
{
	size_t	i;

	i = 0;
	while (in->next_c != FT_EOF && in->next_c != SH_NEWLINE
		&& !ft_strchr(SH_WHITESPACE, in->next_c))
	{
		if (ft_darr_set(dstr, i, &(in->next_c)) != 0)
			return (SH_ERR_NOMEM);
		in->next_c = ft_fgetc(in->stm);
		++i;
	}
	if (ft_darr_set(dstr, i, "\0") != 0)
		return (SH_ERR_NOMEM);
	return (SH_ERR_OK);
}

t_err			sh_parse_word(t_sh_input *in, t_sh_word **word)
{
	t_darray	dstr;
	t_err		err;

	FT_ASSERT(in != NULL);
	FT_ASSERT(word != NULL);
	FT_DEBUG("parse: parsing next word");
	*word = NULL;
	if (skip_whitespace(in))
		return (SH_ERR_OK);
	if (ft_darr_init(&dstr, sizeof(char), 8) != 0)
		return (SH_ERR_NOMEM);
	if ((err = read_word(in, &dstr)))
	{
		ft_darr_clear(&dstr);
		return (err);
	}
	if (!(*word = sh_word_new(dstr.array)))
	{
		ft_darr_clear(&dstr);
		return (SH_ERR_NOMEM);
	}
	FT_DEBUG("parse: parsed word '%s'", (*word)->str);
	return (SH_ERR_OK);
}
