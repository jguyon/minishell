/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_setvar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 16:49:30 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/25 02:50:14 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "sh_errors.h"
#include "ft_memory.h"

static char	*new_var(const char *name, size_t namlen, const char *val)
{
	char	*var;
	size_t	vallen;

	if (!val && name[namlen] == '=')
		return (ft_strdup(name));
	vallen = val ? ft_strlen(val) : 0;
	if (!(var = ft_strnew(namlen + 1 + vallen)))
		return (NULL);
	ft_memcpy(var, name, namlen);
	var[namlen] = '=';
	if (val)
		ft_memcpy(var + namlen + 1, val, vallen);
	return (var);
}

int			sh_env_setvar(t_sh_env *env, const char *name, const char *val)
{
	size_t	i;
	char	**vars;
	size_t	namlen;
	char	*old;
	char	*new;

	vars = env->vars.array;
	i = 0;
	while (vars[i])
	{
		namlen = SH_ENV_NAMLEN(vars[i]);
		if (ft_strncmp(name, vars[i], namlen) == 0
			&& (name[namlen] == '\0' || name[namlen] == '='))
			break ;
		++i;
	}
	if (!(old = vars[i]))
		namlen = SH_ENV_NAMLEN(name);
	if (!(new = new_var(name, namlen, val))
		|| (!old && ft_darr_set(&(env->vars), i + 1, NULL))
		|| ft_darr_set(&(env->vars), i, &new))
		return (SH_ERR_NOMEM);
	ft_memdel((void **)&old);
	return (0);
}
