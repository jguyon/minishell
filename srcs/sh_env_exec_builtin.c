/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_exec_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 01:07:50 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/03 17:15:29 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "ft_streams.h"
#include "ft_debug.h"

int		sh_env_exec_builtin(t_sh_env *env, t_sh_builtin *builtin,
			char *const argv[])
{
	int		argc;
	int		status;

	FT_ASSERT(env != NULL);
	FT_ASSERT(builtin != NULL);
	argc = 0;
	while (argv[argc])
		++argc;
	status = builtin->fn(argc, argv, env);
	ft_fflush(NULL);
	return (status);
}
