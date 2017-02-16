/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 23:45:55 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/16 23:59:20 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include "ft_memory.h"
#include "ft_strings.h"

void	ms_env_unset(t_env *env, const char *name)
{
	size_t	i;
	size_t	name_len;

	name_len = ft_strlen(name);
	i = 0;
	while (i < env->size)
	{
		if (MS_ENV_ISVAR(env->envp[i], name, name_len))
			break ;
		++i;
	}
	if (i < env->size)
	{
		ft_memdel((void **)&(env->envp[i]));
		ft_memmove(env->envp + i, env->envp + i + 1,
			sizeof(*(env->envp)) * (env->size - i));
		env->size -= 1;
	}
}
