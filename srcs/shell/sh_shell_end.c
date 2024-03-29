/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_shell_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 15:46:54 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/03 18:04:08 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_shell.h"
#include "ft_debug.h"

int		sh_shell_end(t_sh_env *env)
{
	int		status;

	FT_ASSERT(env != NULL);
	FT_DEBUG("shell: clear shell for env '%p'", env);
	status = sh_env_status(env);
	sh_env_end(env);
	return (status);
}
