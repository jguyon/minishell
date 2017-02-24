/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 00:01:21 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/24 00:16:05 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "sh_errors.h"
#include "ft_streams.h"
#include "ft_strings.h"

static int			builtin_echo(int ac, char *const av[], t_sh_env *env)
{
	int		i;

	(void)ac;
	(void)env;
	i = 1;
	while (av[i])
	{
		ft_fputs(av[i], FT_STDOUT);
		++i;
		if (av[i])
			ft_fputc(' ', FT_STDOUT);
	}
	ft_fputc('\n', FT_STDOUT);
	return (0);
}

static t_sh_builtin	g_builtins[] = {
	{ "echo", &builtin_echo },
};

int					sh_env_builtin(t_sh_env *env, const char *name,
						t_sh_builtin **builtin)
{
	size_t	i;

	(void)env;
	i = 0;
	*builtin = NULL;
	while (i < sizeof(g_builtins) / sizeof(g_builtins[0]))
	{
		if (ft_strcmp(name, g_builtins[i].name) == 0)
		{
			*builtin = &(g_builtins[i]);
			return (0);
		}
		++i;
	}
	return (SH_ERR_NOTFOUND);
}
