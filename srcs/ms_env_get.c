/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 22:17:09 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/16 23:42:18 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include "ft_strings.h"

const char	*ms_env_get(t_env *env, const char *name)
{
	size_t	i;
	size_t	name_len;

	name_len = ft_strlen(name);
	i = 0;
	while (i < env->size)
	{
		if (MS_ENV_ISVAR(env->envp[i], name, name_len))
			return (env->envp[i] + name_len + 1);
		++i;
	}
	return (NULL);
}
