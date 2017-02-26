/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 02:44:17 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/25 03:00:53 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_builtins.h"
#include "sh_errors.h"
#include "ft_streams.h"
#include "ft_program.h"
#include "ft_strings.h"
#include "ft_memory.h"

static int	start_env(int ac, char *const av[], t_sh_env *old, t_sh_env *new)
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
			ft_error(0, 0, "%s: illegal option -- %c",
				av[0], (char)g_ft_optopt);
			return (FT_EXIT_FAILURE);
		}
	}
	if (sh_env_start(new, clear ? empty : sh_env_vars(old)))
	{
		ft_error(0, SH_ERR_NOMEM, "%s", av[0]);
		return (FT_EXIT_FAILURE);
	}
	return (0);
}

static int	edit_env(t_sh_env *env, int ac, char *const av[])
{
	while (g_ft_optind < ac)
	{
		if (!ft_strchr(av[g_ft_optind], '='))
			break ;
		if (sh_env_setvar(env, av[g_ft_optind], NULL))
		{
			ft_error(0, SH_ERR_NOMEM, "%s", av[0], av[g_ft_optind]);
			return (FT_EXIT_FAILURE);
		}
		++g_ft_optind;
	}
	return (0);
}

static void	print_env(t_sh_env *env)
{
	size_t		i;
	char *const	*envp;

	if ((envp = sh_env_vars(env)))
	{
		i = 0;
		while (envp[i])
		{
			ft_fputs(envp[i], FT_STDOUT);
			ft_fputc('\n', FT_STDOUT);
			++i;
		}
	}
}

static int	exec_util(t_sh_env *env, char *const av[])
{
	int		err;

	if ((err = sh_env_exec(env, av + g_ft_optind)))
	{
		ft_error(0, err, "%s: %s", av[0], av[g_ft_optind]);
		return (FT_EXIT_FAILURE);
	}
	return (0);
}

int			sh_builtin_env(int ac, char *const av[], t_sh_env *env)
{
	t_sh_env	new;
	int			status;

	if ((status = start_env(ac, av, env, &new)))
		return (status);
	if ((status = edit_env(&new, ac, av)))
	{
		sh_env_end(&new);
		return (status);
	}
	status = 0;
	if (g_ft_optind >= ac)
		print_env(&new);
	else
		status = exec_util(&new, av);
	sh_env_end(&new);
	return (status);
}