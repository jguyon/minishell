/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 02:04:50 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/03 16:54:01 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "ft_debug.h"

int		sh_env_status(t_sh_env *env)
{
	FT_ASSERT(env != NULL);
	return (env->exit_status);
}
