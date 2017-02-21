/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 13:37:29 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/21 22:59:42 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "ms_errors.h"
#include "ft_program.h"
#include "ft_streams.h"
#include <unistd.h>

int		ms_builtin_pwd(int ac, char *const av[], t_env *env)
{
	char	*pwd;

	(void)ac;
	(void)av;
	(void)env;
	if (!(pwd = getcwd(NULL, 0)))
	{
		ms_error(0, MS_ERR_IO, "%s", av[0]);
		return (FT_EXIT_FAILURE);
	}
	ft_fputs(pwd, FT_STDOUT);
	ft_fputc('\n', FT_STDOUT);
	free(pwd);
	return (FT_EXIT_SUCCESS);
}
