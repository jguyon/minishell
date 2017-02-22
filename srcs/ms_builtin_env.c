/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 14:14:54 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/22 14:31:26 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "ms_errors.h"
#include "ft_streams.h"
#include "ft_program.h"
#include "ft_strings.h"
#include "ft_memory.h"

static int	start_env(int ac, char *const av[], t_env *old, t_env *new)
{
	int		clear;
	char	*empty[1];
	int		opt;

	g_ft_opterr = 0;
	g_ft_optind = 0;
	clear = 0;
	empty[0] = NULL;
	while ((opt = ft_getopt(ac, av, "i")) != -1)
	{
		if (opt == 'i')
			clear = 1;
		else
		{
			ms_error(0, 0, "%s: illegal option -- %c",
				av[0], (char)g_ft_optopt);
			return (FT_EXIT_FAILURE);
		}
	}
	if (ms_env_start(new, clear ? empty : old->envp))
	{
		ms_error(0, MS_ERR_NOMEM, "%s", av[0]);
		return (FT_EXIT_FAILURE);
	}
	return (0);
}

static int	edit_env(t_env *env, int ac, char *const av[])
{
	char	*var;

	while (g_ft_optind < ac)
	{
		if (!(var = ft_strchr(av[g_ft_optind], '=')))
			break ;
		if (ms_env_set(env, av[g_ft_optind], var + 1))
		{
			ms_error(0, MS_ERR_NOMEM, "%s", av[0], av[g_ft_optind]);
			return (FT_EXIT_FAILURE);
		}
		++g_ft_optind;
	}
	return (0);
}

static void	print_env(t_env *env)
{
	size_t	i;

	i = 0;
	while (env->envp[i])
	{
		ft_fputs(env->envp[i], FT_STDOUT);
		ft_fputc('\n', FT_STDOUT);
		++i;
	}
}

static int	exec_util(t_env *env, char *const av[])
{
	t_builtin	*builtin;
	char		*path;

	if ((builtin = ms_resolve_builtin(av[g_ft_optind])))
		ms_exec_builtin(env, builtin, &(av[g_ft_optind]));
	else if ((path = ms_resolve_path(env, av[g_ft_optind])))
	{
		ms_exec_bin(env, path, &(av[g_ft_optind]));
		ft_memdel((void **)&path);
	}
	else
	{
		ms_error(0, MS_ERR_NOTFOUND, "%s: %s", av[0], av[g_ft_optind]);
		return (FT_EXIT_FAILURE);
	}
	return (0);
}

int			ms_builtin_env(int ac, char *const av[], t_env *env)
{
	t_env	new;
	int		status;

	if ((status = start_env(ac, av, env, &new)))
		return (status);
	if ((status = edit_env(&new, ac, av)))
	{
		ms_env_end(&new);
		return (status);
	}
	status = 0;
	if (g_ft_optind >= ac)
		print_env(&new);
	else
		status = exec_util(&new, av);
	ms_env_end(&new);
	return (status);
}
