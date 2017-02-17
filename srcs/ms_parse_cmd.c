/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 01:20:18 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/17 03:17:48 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_memory.h"
#include "ft_strings.h"
#include <limits.h>

static const char	*next_word(const char *str, const char **end)
{
	const char	*start;

	start = str;
	while (*start && (*start == ' ' || *start == '\t' || *start == '\n'))
		++start;
	if (!(*start))
		return (NULL);
	*end = start + 1;
	while (**end && **end != ' ' && **end != '\t' && **end != '\n')
		++(*end);
	return (start);
}

static char			*dup_cmd_name(const char *str, const char **args)
{
	const char	*start;
	const char	*end;
	char		*name;

	if (!(start = next_word(str, &end)))
		return (NULL);
	if (!(name = ft_strsub(start, 0, end - start)))
		return (NULL);
	*args = end;
	return (name);
}

static ssize_t		push_cmd_args(t_dlist *lst, const char *args)
{
	const char	*start;
	const char	*end;
	t_arg		*arg;
	size_t		size;

	start = args;
	size = 0;
	while ((start = next_word(start, &end)))
	{
		if (!(arg = (t_arg *)ft_memalloc(sizeof(*arg) + (end - start) + 1)))
			return (-1);
		ft_memcpy(arg->str, start, end - start);
		ft_dlst_pushr(lst, &(arg->node));
		start = end;
		++size;
	}
	return (size);
}

t_cmd				*ms_parse_cmd(t_stream *stm)
{
	char		str[LINE_MAX + 1];
	t_cmd		*cmd;
	char		*name;
	const char		*args;
	ssize_t		count;

	if (!(ft_fgets(str, sizeof(str), stm)))
		return (NULL);
	if (!(name = dup_cmd_name(str, &args))
		|| !(cmd = (t_cmd *)ft_memalloc(sizeof(*cmd))))
	{
		ft_strdel(&name);
		return (NULL);
	}
	cmd->name = name;
	FT_DLST_INIT(&(cmd->args), t_arg, node);
	if ((count = push_cmd_args(&(cmd->args), args)) < 0)
	{
		ms_destroy_cmd(&cmd);
		return (NULL);
	}
	cmd->arg_count = (size_t)count;
	return (cmd);
}
