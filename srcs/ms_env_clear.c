/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 00:02:29 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/17 00:03:47 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include "ft_memory.h"

void	ms_env_clear(t_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->size)
	{
		ft_memdel((void **)&(env->envp[i]));
		++i;
	}
	env->size = 0;
}
