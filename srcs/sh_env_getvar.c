/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_getvar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 16:42:17 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/23 18:32:42 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"

const char	*sh_env_getvar(t_sh_env *env, const char *name)
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
			return (vars[i] + namlen + 1);
		++i;
	}
	return (NULL);
}
