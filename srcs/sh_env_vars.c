/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 18:00:27 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/03 15:35:43 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "ft_debug.h"

char *const	*sh_env_vars(t_sh_env *env)
{
	FT_ASSERT(env != NULL);
	return (env->vars.array);
}
