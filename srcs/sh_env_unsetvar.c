/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_unsetvar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 19:22:33 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/23 19:30:48 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "ft_memory.h"

void	sh_env_unsetvar(t_sh_env *env, const char *name)
{
	size_t		i;
	char		**vars;
	size_t		namlen;

	vars = env->vars.array;
	i = 0;
	while (vars[i])
	{
		namlen = SH_ENV_NAMLEN(vars[i]);
		if (ft_strncmp(name, vars[i], namlen) == 0 && name[namlen] == '\0')
			break ;
		++i;
	}
	if (vars[i])
	{
		ft_memdel((void **)&(vars[i]));
		vars[i] = vars[i + 1];
		++i;
		while (vars[i])
		{
			vars[i] = vars[i + 1];
			++i;
		}
	}
}
