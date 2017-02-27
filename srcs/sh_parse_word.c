/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parse_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:37:19 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/27 17:21:06 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_parse.h"
#include "sh_errors.h"
#include "ft_strings.h"
#include "ft_darrays.h"

static int	skip_whitespace(t_sh_input *in)
{
	while (ft_strchr(SH_WHITESPACE, in->next_c))
		in->next_c = ft_fgetc(in->stm);
	if (in->next_c == FT_EOF || in->next_c == SH_NEWLINE)
		return (-1);
	return (0);
}

static int	read_word(t_sh_input *in, t_darray *dstr)
{
	size_t	i;
	int		err;

	i = 0;
	while (in->next_c != FT_EOF && in->next_c != SH_NEWLINE
		&& !ft_strchr(SH_WHITESPACE, in->next_c))
	{
		if ((err = ft_darr_set(dstr, i, &(in->next_c))) != 0)
			return (err);
		in->next_c = ft_fgetc(in->stm);
		++i;
	}
	if ((err = ft_darr_set(dstr, i, "\0")) != 0)
		return (err);
	return (0);
}

int			sh_parse_word(t_sh_input *in, t_sh_word **word)
{
	t_darray	dstr;
	int			err;

	*word = NULL;
	if (skip_whitespace(in))
		return (-1);
	if ((err = ft_darr_init(&dstr, NULL, sizeof(char), 8)) != 0)
		return (err);
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
	return (0);
}
