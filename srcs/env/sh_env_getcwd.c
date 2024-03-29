/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_getcwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 01:27:27 by jguyon            #+#    #+#             */
/*   Updated: 2017/05/04 17:40:39 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "ft_debug.h"
#include <unistd.h>

t_sh_err	sh_env_getcwd(t_sh_env *env, int nosym, char **cwd)
{
	FT_ASSERT(env != NULL);
	FT_ASSERT(cwd != NULL);
	*cwd = NULL;
	if (nosym && !(*cwd = getcwd(NULL, 0)))
		return (SH_ERR_IO);
	else if (!nosym && !(*cwd = ft_strdup(env->cwd)))
		return (SH_ERR_NOMEM);
	return (SH_ERR_OK);
}
