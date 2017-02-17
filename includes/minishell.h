/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 00:50:36 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/17 03:51:50 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_dlists.h"
# include "ft_streams.h"
# include <stddef.h>

/*
** Types for representing a command and its args
*/

typedef struct	s_cmd {
	char		*name;
	size_t		arg_count;
	t_dlist		args;
}				t_cmd;

typedef struct	s_arg {
	t_dlist_node	node;
	char			str[];
}				t_arg;

/*
** Parse a command from a stream
*/
t_cmd			*ms_parse_cmd(t_stream *stm);

/*
** Free memory associated with a command
*/
void			ms_destroy_cmd(t_cmd **cmd);

#endif
