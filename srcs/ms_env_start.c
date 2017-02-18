/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 21:50:49 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/18 16:55:06 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include "ft_memory.h"
#include "ft_strings.h"

int		ms_env_start(t_env *env, char **envp)
{
	size_t	size;

	size = 0;
	while (envp[size])
		++size;
	env->size = size;
	env->alloc_size = size;
	if (!(env->envp = (char **)ft_memalloc(sizeof(*(env->envp)) * (size + 1))))
		return (-1);
	while (size)
	{
		--size;
		if (!(env->envp[size] = ft_strdup(envp[size])))
		{
			ms_env_end(env);
			return (-1);
		}
	}
	return (0);
}
