/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parse.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 15:59:10 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/24 22:12:05 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PARSE_H
# define SH_PARSE_H

# include "sh_ast.h"
# include "ft_streams.h"

# define SH_NEWLINE		'\n'
# define SH_WHITESPACE	" \t"

typedef struct	s_sh_input {
	int			next_c;
	t_stream	*stm;
}				t_sh_input;

int				sh_init_input(t_sh_input *in, t_stream *stm);
int				sh_parse_word(t_sh_input *in, t_sh_word **word);
int				sh_parse_cmd(t_sh_input *in, t_sh_cmd **cmd);

#endif
