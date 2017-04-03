/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 16:29:20 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/03 13:09:58 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "sh_errors.h"
#include "ft_memory.h"
#include <unistd.h>

int		sh_env_start(t_sh_env *env, char *const envp[])
{
	size_t	size;
	char	**vars;

	env->exit_status = SH_EXIT_SUCCESS;
	env->should_exit = 0;
	if (!(env->cwd = getcwd(NULL, 0)))
		return (SH_ERR_IO);
	size = 0;
	while (envp[size])
		++size;
	if (ft_darr_init(&(env->vars), sizeof(envp[0]), size + 1))
		return (SH_ERR_NOMEM);
	vars = env->vars.array;
	while (size)
	{
		--size;
		if (!(vars[size] = ft_strdup(envp[size])))
		{
			ft_memdel((void **)&(vars[size]));
			sh_env_end(env);
			return (SH_ERR_NOMEM);
		}
	}
	return (0);
}
