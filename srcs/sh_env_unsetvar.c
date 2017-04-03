/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_unsetvar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 19:22:33 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/03 18:28:58 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "ft_memory.h"
#include "ft_debug.h"

static size_t	find_var(char *const envp[], const char *name)
{
	size_t	i;
	size_t	namlen;

	i = 0;
	while (envp[i])
	{
		namlen = SH_ENV_NAMLEN(envp[i]);
		if (ft_strncmp(name, envp[i], namlen) == 0 && name[namlen] == '\0')
			break ;
		++i;
	}
	return (i);
}

static void		unset_var(char **envp[], size_t i)
{
	if (envp[i])
	{
		ft_memdel((void **)&(envp[i]));
		envp[i] = envp[i + 1];
		++i;
		while (envp[i])
		{
			envp[i] = envp[i + 1];
			++i;
		}
	}
}

void			sh_env_unsetvar(t_sh_env *env, const char *name)
{
	size_t		i;

	FT_ASSERT(env != NULL);
	FT_ASSERT(name != NULL);
	i = find_var(env->vars.array, name);
	unset_var(env->vars.array, i);
	FT_DEBUG("env: unset var '%s'", name);
}
