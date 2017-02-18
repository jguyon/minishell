/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 14:14:54 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/18 18:41:09 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "ft_streams.h"
#include "ft_program.h"

int		ms_builtin_env(int ac, char *const av[], t_env *env)
{
	size_t	i;

	(void)ac;
	(void)av;
	i = 0;
	while (env->envp[i])
	{
		ft_fputs(env->envp[i], FT_STDOUT);
		ft_fputc('\n', FT_STDOUT);
		++i;
	}
	return (FT_EXIT_SUCCESS);
}
