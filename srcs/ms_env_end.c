/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 21:52:55 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/17 20:08:03 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include "ft_memory.h"

static int	destroy_bin(void *entry, void *acc)
{
	(void)acc;
	ft_dlst_remove(&((t_bin *)entry)->node);
	ft_memdel((void **)&(((t_bin *)entry)->file));
	ft_memdel(&entry);
	return (1);
}

void		ms_env_end(t_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->size)
	{
		ft_memdel((void **)&(env->envp[i]));
		++i;
	}
	ft_dlst_foreachl(&(env->bins), NULL, &destroy_bin);
	ft_memdel((void **)&(env->envp));
}
