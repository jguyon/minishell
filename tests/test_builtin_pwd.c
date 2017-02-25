/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin_pwd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 23:00:22 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/25 02:20:09 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "sh_builtins.h"
#include "ft_strings.h"
#include <unistd.h>
#include <stdlib.h>

static void	test_dir(t_tap *t)
{
	char		*ep[] = {NULL};
	char		*av[] = {"pwd", NULL};
	t_sh_env	env;
	char		*pwd;
	char		*all;

	pwd = getcwd(NULL, 0);
	all = ft_strjoin(pwd, "\n");
	ft_tap_plan(t, 2);
	if (sh_env_start(&env, ep) == 0)
	{
		FT_TAP_IEQ(t, sh_builtin_pwd(1, av, &env), 0);
		STDOUT_EQ(t, all);
		sh_env_end(&env);
	}
	free(pwd);
	free(all);
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_dir);
}
