/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 03:04:10 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/04 12:48:39 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_builtins.h"
#include "ft_program.h"
#include "ft_chars.h"

static int	strtoi(const char *str)
{
	unsigned int	n;

	if (*str == '\0')
		return (-1);
	n = 0;
	while (ft_isdigit(*str))
	{
		n = 10 * n + (*str - '0');
		if (n > 255)
			return (-1);
		++str;
	}
	if (*str != '\0')
		return (-1);
	return (n);
}

int			sh_builtin_exit(int ac, char *const av[], t_sh_env *env)
{
	int		status;

	if (ac > 2)
	{
		ft_error(0, SH_ERR_ARGS2BIG, "%s", av[0]);
		return (FT_EXIT_FAILURE);
	}
	else if (ac < 2)
		status = sh_env_status(env);
	else if ((status = strtoi(av[1])) < 0)
	{
		ft_error(0, SH_ERR_BADNUM, "%s: %s", av[0], av[1]);
		sh_env_exit(env, FT_EXIT_FAILURE);
		return (FT_EXIT_FAILURE);
	}
	sh_env_exit(env, status);
	return (status);
}
