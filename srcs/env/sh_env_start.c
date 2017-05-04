/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 16:29:20 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/04 12:20:29 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "ft_memory.h"
#include "ft_debug.h"
#include <unistd.h>

static t_err	get_wd(char **wd)
{
	if (!(*wd = getcwd(NULL, 0)))
		return (SH_ERR_IO);
	return (SH_ERR_OK);
}

static t_err	copy_env(t_darray *arr, char *const envp[])
{
	size_t	size;
	char	*var;

	size = 0;
	while (envp[size])
		++size;
	if (ft_darr_set(arr, size, NULL))
		return (SH_ERR_NOMEM);
	while (size)
	{
		--size;
		if (!(var = ft_strdup(envp[size])))
			return (SH_ERR_NOMEM);
		if (ft_darr_set(arr, size, &var))
		{
			ft_memdel((void **)&var);
			return (SH_ERR_NOMEM);
		}
	}
	return (SH_ERR_OK);
}

t_err			sh_env_start(t_sh_env *env, char *const envp[])
{
	t_err	err;

	FT_ASSERT(env != NULL);
	FT_ASSERT(envp != NULL);
	env->exit_status = SH_EXIT_SUCCESS;
	env->should_exit = 0;
	env->cwd = NULL;
	if (ft_darr_init(&(env->vars), sizeof(envp[0]), 0))
		return (SH_ERR_NOMEM);
	if ((err = get_wd(&(env->cwd)))
		|| (err = copy_env(&(env->vars), envp)))
	{
		sh_env_end(env);
		return (err);
	}
	FT_DEBUG("env: initialized env '%p'", env);
	return (SH_ERR_OK);
}
