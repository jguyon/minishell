/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_pipelist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:02:34 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/13 17:05:48 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_exec.h"
#include "ft_debug.h"

t_err	sh_exec_pipelist(t_sh_env *env, t_sh_pipelist **pipe)
{
	t_sh_cmd	*cmd;
	t_err		err;

	FT_ASSERT(env != NULL);
	FT_ASSERT(pipe != NULL);
	err = SH_ERR_OK;
	if ((cmd = sh_pipelist_pop(*pipe)))
		err = sh_exec_cmd(env, &cmd);
	sh_pipelist_del(pipe);
	return (err);
}
