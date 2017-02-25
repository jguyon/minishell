/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 03:04:10 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/25 03:13:41 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_builtins.h"
#include "ft_numbers.h"

int		sh_builtin_exit(int ac, char *const av[], t_sh_env *env)
{
	int		status;

	status = ac > 1 ? ft_atoi(av[1]) : sh_env_status(env);
	sh_env_exit(env, status);
	return (status);
}
