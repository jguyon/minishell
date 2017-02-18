/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 12:47:31 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/18 18:40:22 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "ft_program.h"
#include <unistd.h>
#include <stdlib.h>

int		ms_builtin_cd(int ac, char *const av[], t_env *env)
{
	char	*oldpwd;
	char	*newpwd;

	if (!(oldpwd = getcwd(NULL, 0)))
		return (FT_EXIT_FAILURE);
	if (ac < 2 || !(newpwd = av[1]) || chdir(newpwd))
	{
		free(oldpwd);
		return (FT_EXIT_FAILURE);
	}
	ms_env_set(env, "OLDPWD", oldpwd);
	ms_env_set(env, "PWD", newpwd);
	free(oldpwd);
	return (FT_EXIT_SUCCESS);
}
