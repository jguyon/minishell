/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_setvar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 16:49:30 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/04 12:52:56 by jguyon           ###   ########.fr       */
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
		if (ft_strncmp(name, envp[i], namlen) == 0
			&& (name[namlen] == '\0' || name[namlen] == '='))
			break ;
		++i;
	}
	return (i);
}

static char		*new_var(const char *name, size_t namlen, const char *val)
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

static t_err	set_var(t_darray *arr, const char *name, const char *val,
						size_t i)
{
	size_t	namlen;
	char	**vars;
	char	*old;
	char	*new;

	vars = arr->array;
	old = vars[i];
	namlen = SH_ENV_NAMLEN(name);
	new = NULL;
	if (!(new = new_var(name, namlen, val))
		|| (!old && ft_darr_set(arr, i + 1, NULL))
		|| ft_darr_set(arr, i, &new))
	{
		ft_memdel((void **)&new);
		return (SH_ERR_NOMEM);
	}
	FT_DEBUG("env: set var '%s' to '%s'", name, new);
	ft_memdel((void **)&old);
	return (SH_ERR_OK);
}

int				sh_env_setvar(t_sh_env *env, const char *name, const char *val)
{
	size_t	i;

	FT_ASSERT(env != NULL);
	FT_ASSERT(name != NULL);
	i = find_var(env->vars.array, name);
	return (set_var(&(env->vars), name, val, i));
}
