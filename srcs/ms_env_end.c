/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 21:52:55 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/16 21:57:11 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include "ft_memory.h"

void	ms_env_end(t_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->size)
	{
		ft_memdel((void **)&(env->envp[i]));
		++i;
	}
	ft_memdel((void **)&(env->envp));
}
