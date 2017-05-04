/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 01:09:25 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/25 01:10:45 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_builtins.h"
#include "ft_printf.h"

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

int			sh_builtin_echo(int ac, char *const av[], t_sh_env *env)
{
	(void)env;
	(void)ac;
	if (av[1] && ft_strcmp(av[1], "-n") == 0)
		echo_strings(&(av[2]), 1);
	else
		echo_strings(&(av[1]), 0);
	return (0);
}
