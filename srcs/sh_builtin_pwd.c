/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 02:18:40 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/25 02:19:30 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_builtins.h"
#include "sh_errors.h"
#include "ft_program.h"
#include "ft_streams.h"
#include <unistd.h>

int		sh_builtin_pwd(int ac, char *const av[], t_sh_env *env)
{
	char	*pwd;

	(void)ac;
	(void)av;
	(void)env;
	if (!(pwd = getcwd(NULL, 0)))
	{
		ft_error(0, SH_ERR_IO, "%s", av[0]);
		return (FT_EXIT_FAILURE);
	}
	ft_fputs(pwd, FT_STDOUT);
	ft_fputc('\n', FT_STDOUT);
	free(pwd);
	return (FT_EXIT_SUCCESS);
}
