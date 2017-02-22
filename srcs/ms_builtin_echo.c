/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 17:00:21 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/21 18:25:45 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "ms_errors.h"
#include "ft_program.h"
#include "ft_printf.h"
#include "ft_strings.h"

static void	echo_strings(char *const strs[], int no_newline)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		ft_fputs(strs[i], FT_STDOUT);
		++i;
		if (strs[i])
			ft_fputc(' ', FT_STDOUT);
	}
	if (!no_newline)
		ft_fputc('\n', FT_STDOUT);
}

int			ms_builtin_echo(int ac, char *const av[], t_env *env)
{
	(void)env;
	(void)ac;
	if (av[1] && ft_strcmp(av[1], "-n") == 0)
		echo_strings(&(av[2]), 1);
	else
		echo_strings(&(av[1]), 0);
	if (ft_ferror(FT_STDOUT))
	{
		ms_error(0, MS_ERR_IO, "%s", av[0]);
		return (FT_EXIT_FAILURE);
	}
	return (FT_EXIT_SUCCESS);
}
