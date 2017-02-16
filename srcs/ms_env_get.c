/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 22:17:09 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/16 22:25:23 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include "ft_strings.h"

const char	*ms_env_get(t_env *env, const char *name)
{
	size_t	i;
	char	*name_end;

	i = 0;
	while (i < env->size)
	{
		if ((name_end = ft_strchr(env->envp[i], '='))
			&& ft_strncmp(env->envp[i], name, name_end - env->envp[i]) == 0)
			return (name_end + 1);
		++i;
	}
	return (NULL);
}
