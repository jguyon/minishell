/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 01:39:15 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/03 18:38:01 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "ft_debug.h"

void	sh_env_exit(t_sh_env *env, int status)
{
	FT_ASSERT(env);
	if (status >= 0)
		env->exit_status = SH_EXIT_STATUS(status);
	env->should_exit = 1;
	FT_DEBUG("env: mark env for exit with '%d'", status);
}
