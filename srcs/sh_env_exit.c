/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 01:39:15 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/24 01:42:06 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"

void	sh_env_exit(t_sh_env *env, int status)
{
	if (status >= 0)
		env->exit_status = SH_EXIT_STATUS(status);
	env->should_exit = 1;
}
