/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_exec_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 01:07:50 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/24 01:10:42 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "ft_streams.h"

int		sh_env_exec_builtin(t_sh_env *env, t_sh_builtin *builtin,
			char *const argv[])
{
	int		argc;
	int		status;

	argc = 0;
	while (argv[argc])
		++argc;
	status = builtin->fn(argc, argv, env);
	ft_fflush(NULL);
	return (status);
}
