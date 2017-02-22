/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 22:32:41 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/21 23:32:17 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include "ft_memory.h"
#include "ft_strings.h"

static int	grow_env(t_env *env)
{
	char	**envp;
	size_t	size;
	size_t	i;

	size = env->alloc_size ? env->alloc_size * 2 : 1;
	if (!(envp = (char **)ft_memalloc(sizeof(*envp) * (size + 1))))
		return (-1);
	i = 0;
	while (i < env->size)
	{
		envp[i] = env->envp[i];
		++i;
	}
	ft_memdel((void **)&(env->envp));
	env->alloc_size = size;
	env->size += 1;
	env->envp = envp;
	return (0);
}

static char	*new_var(const char *name, size_t name_len,
				const char *value, size_t value_len)
{
	char	*var;

	if (!(var = ft_strnew(name_len + 1 + value_len)))
		return (NULL);
	ft_memcpy(var, name, name_len);
	var[name_len] = '=';
	ft_memcpy(var + name_len + 1, value, value_len);
	return (var);
}

int			ms_env_set(t_env *env, const char *name, const char *value)
{
	size_t	i;
	size_t	name_len;
	char	*var;

	name_len = ft_strchrnul(name, '=') - name;
	i = 0;
	while (i < env->size)
	{
		if (MS_ENV_ISVAR(env->envp[i], name, name_len))
			break ;
		++i;
	}
	if (i >= env->alloc_size && grow_env(env))
		return (-1);
	if (!(var = new_var(name, name_len, value, ft_strlen(value))))
		return (-1);
	ft_memdel((void **)&(env->envp[i]));
	env->envp[i] = var;
	return (0);
}
