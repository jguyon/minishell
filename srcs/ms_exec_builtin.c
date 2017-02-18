/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 18:34:08 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/18 18:39:27 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"

void	ms_exec_builtin(t_env *env, t_builtin *bt, char *const argv[])
{
	int		argc;

	argc = 0;
	while (argv[argc])
		++argc;
	bt->fn(argc, argv, env);
}
