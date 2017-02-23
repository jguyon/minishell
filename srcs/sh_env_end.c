/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 16:33:45 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/23 18:36:55 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "ft_memory.h"

void	sh_env_end(t_sh_env *env)
{
	size_t	i;
	char	**vars;

	vars = env->vars.array;
	i = 0;
	while (vars[i])
	{
		ft_memdel((void **)&vars[i]);
		++i;
	}
	ft_darr_clear(&(env->vars));
}
