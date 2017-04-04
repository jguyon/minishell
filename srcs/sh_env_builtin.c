/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 00:01:21 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/04 12:34:23 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
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

t_err				sh_env_builtin(t_sh_env *env, const char *name,
						t_sh_builtin **builtin)
{
	size_t	i;

	FT_ASSERT(env != NULL);
	FT_ASSERT(name != NULL);
	FT_ASSERT(builtin != NULL);
	FT_DEBUG("env: searching for built-in '%s'", name);
	(void)env;
	i = 0;
	*builtin = NULL;
	while (i < sizeof(g_builtins) / sizeof(g_builtins[0]))
	{
		if (ft_strcmp(name, g_builtins[i].name) == 0)
		{
			*builtin = &(g_builtins[i]);
			FT_DEBUG("env: found built-in '%s'", name);
			return (SH_ERR_OK);
		}
		++i;
	}
	return (SH_ERR_NOCMD);
}
