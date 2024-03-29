/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_seqlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 21:05:59 by jguyon            #+#    #+#             */
/*   Updated: 2017/05/04 17:55:29 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_exec.h"
#include "ft_debug.h"

t_sh_err	sh_exec_seqlist(t_sh_env *env, t_sh_seqlist **lst)
{
	t_sh_pipelist	*pipe;
	t_sh_err		err;

	FT_ASSERT(env != NULL);
	FT_ASSERT(lst != NULL);
	err = SH_ERR_OK;
	while ((pipe = sh_seqlist_pop(*lst))
			&& (err = sh_exec_pipelist(env, &pipe)) == SH_ERR_OK)
		;
	sh_seqlist_del(lst);
	return (err);
}
