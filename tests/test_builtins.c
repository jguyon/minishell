/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 13:21:19 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/21 20:53:31 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "ms_builtins.h"
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static void	test_pwd(t_tap *t)
{
	t_env	env;
	char	*envp[] = {NULL};
	char	pwd[PATH_MAX];
	char	*argv[] = {"pwd", NULL};

	ft_tap_plan(t, 2);
	if (!getcwd(pwd, PATH_MAX) || ms_env_start(&env, envp))
		return ;
	strcpy(pwd + strlen(pwd), "\n");
	FT_TAP_IEQ(t, ms_builtin_pwd(1, argv, &env), 0);
	STDOUT_EQ(t, pwd);
	ms_env_end(&env);
}

static void	test_env(t_tap *t)
{
	t_env	env;
	char	*envp[] = {"USER=john", "HOME=/home/john", NULL};
	char	*argv[] = {"env", NULL};

	ft_tap_plan(t, 2);
	if (!ms_env_start(&env, envp))
	{
		FT_TAP_IEQ(t, ms_builtin_env(1, argv, &env), 0);
		STDOUT_EQ(t, "USER=john\nHOME=/home/john\n");
		ms_env_end(&env);
	}
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_pwd);
	FT_TAP_TEST(t, test_env);
}
