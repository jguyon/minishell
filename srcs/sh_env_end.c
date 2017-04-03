/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 16:33:45 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/03 18:26:47 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "ft_memory.h"
#include "ft_debug.h"

void	sh_env_end(t_sh_env *env)
{
	size_t	i;
	char	**vars;

	FT_ASSERT(env != NULL);
	ft_memdel((void **)&(env->cwd));
	vars = env->vars.array;
	i = 0;
	while (vars[i])
	{
		ft_memdel((void **)&vars[i]);
		++i;
	}
	ft_darr_clear(&(env->vars));
	FT_DEBUG("env: cleared env '%p'", env);
}
