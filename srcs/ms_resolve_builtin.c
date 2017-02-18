/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_resolve_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 18:15:16 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/18 19:02:31 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include "ms_builtins.h"
#include "ft_strings.h"

static t_builtin	g_builtins[] = {
	{ .name = "cd", .fn = &ms_builtin_cd },
	{ .name = "pwd", .fn = &ms_builtin_pwd },
	{ .name = "env", .fn = &ms_builtin_env },
};

t_builtin			*ms_resolve_builtin(const char *name)
{
	size_t	i;

	i = 0;
	while (i < sizeof(g_builtins) / sizeof(*g_builtins))
	{
		if (ft_strcmp(g_builtins[i].name, name) == 0)
			return (&(g_builtins[i]));
		++i;
	}
	return (NULL);
}
