/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 13:37:29 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/18 14:13:56 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "ft_program.h"
#include "ft_streams.h"
#include <unistd.h>

int		ms_builtin_pwd(int ac, char *av[], t_env *env)
{
	char	*pwd;

	(void)ac;
	(void)av;
	(void)env;
	if (!(pwd = getcwd(NULL, 0)))
		return (FT_EXIT_FAILURE);
	ft_fputs(pwd, FT_STDOUT);
	ft_fputc('\n', FT_STDOUT);
	free(pwd);
	return (FT_EXIT_SUCCESS);
}
