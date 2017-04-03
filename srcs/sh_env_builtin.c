/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 00:01:21 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/03 17:15:54 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "sh_errors.h"
#include "sh_builtins.h"
#include "ft_strings.h"
#include "ft_debug.h"

static t_sh_builtin	g_builtins[] = {
	{ "echo", &sh_builtin_echo },
	{ "cd", &sh_builtin_cd },
	{ "pwd", &sh_builtin_pwd },
	{ "setenv", &sh_builtin_setenv },
	{ "unsetenv", &sh_builtin_unsetenv },
	{ "env", &sh_builtin_env },
	{ "exit", &sh_builtin_exit },
};

int					sh_env_builtin(t_sh_env *env, const char *name,
						t_sh_builtin **builtin)
{
	size_t	i;

	FT_ASSERT(env != NULL);
	FT_ASSERT(name != NULL);
	FT_ASSERT(builtin != NULL);
	(void)env;
	i = 0;
	*builtin = NULL;
	while (i < sizeof(g_builtins) / sizeof(g_builtins[0]))
	{
		if (ft_strcmp(name, g_builtins[i].name) == 0)
		{
			*builtin = &(g_builtins[i]);
			return (0);
		}
		++i;
	}
	return (SH_ERR_NOCMD);
}
