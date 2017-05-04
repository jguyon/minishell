/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec_pipelist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 18:40:42 by jguyon            #+#    #+#             */
/*   Updated: 2017/05/04 17:56:54 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "sh_exec.h"
#include "ft_streams.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

static void	test_empty(t_tap *t)
{
	char			*envp[] = {"PATH=/bin:/usr/bin", NULL};
	t_sh_pipelist	*lst;
	t_sh_env		env;

	sh_env_start(&env, envp);
	lst = sh_pipelist_new();
	FT_TAP_IEQ(t, sh_exec_pipelist(&env, &lst), 0);
	FT_TAP_OK(t, lst == NULL);
	sh_env_end(&env);
}

static void	test_singleton(t_tap *t)
{
	char			*envp[] = {"PATH=/bin:/usr/bin", NULL};
	t_sh_pipelist	*lst;
	t_sh_cmd		*cmd;
	t_sh_env		env;

	sh_env_start(&env, envp);
	lst = sh_pipelist_new();
	cmd = sh_cmd_new(sh_word_new(strdup("setenv")));
	sh_cmd_push(cmd, sh_word_new(strdup("PATH")));
	sh_cmd_push(cmd, sh_word_new(strdup("/home/john/.local/bin")));
	sh_pipelist_push(lst, cmd);
	FT_TAP_IEQ(t, sh_exec_pipelist(&env, &lst), 0);
	FT_TAP_OK(t, lst == NULL);
	FT_TAP_SEQ(t, sh_env_getvar(&env, "PATH"), "/home/john/.local/bin");
	sh_env_end(&env);
}

static void	test_multiple(t_tap *t)
{
	char			*envp[] = {"PATH=/bin:/usr/bin", NULL};
	t_sh_pipelist	*lst;
	t_sh_cmd		*cmd;
	t_sh_env		env;
	t_sh_err		err;
	int				outfd;
	int				tmpfd;
	char			buf[256] = {0};

	sh_env_start(&env, envp);
	lst = sh_pipelist_new();
	cmd = sh_cmd_new(sh_word_new(strdup("echo")));
	sh_cmd_push(cmd, sh_word_new(strdup("-n")));
	sh_cmd_push(cmd, sh_word_new(strdup("hello warld\nhella world\n")));
	sh_pipelist_push(lst, cmd);
	cmd = sh_cmd_new(sh_word_new(strdup("tr")));
	sh_cmd_push(cmd, sh_word_new(strdup("a")));
	sh_cmd_push(cmd, sh_word_new(strdup("o")));
	fflush(NULL);
	sh_pipelist_push(lst, cmd);
	cmd = sh_cmd_new(sh_word_new(strdup("cat")));
	sh_cmd_push(cmd, sh_word_new(strdup("-e")));
	sh_pipelist_push(lst, cmd);
	ft_fclose(FT_STDOUT);
	FT_STDOUT = ft_fdopen(1, "w");
	tmpfd = open("/tmp/test_multiple_pipes", O_CREAT | O_TRUNC | O_RDWR);
	chmod("/tmp/test_multiple_pipes", S_IRWXU);
	outfd = dup(1);
	dup2(tmpfd, 1);
	err = sh_exec_pipelist(&env, &lst);
	lseek(tmpfd, 0, SEEK_SET);
	stdout_reopen();
	(void)read(tmpfd, buf, sizeof(buf));
	close(tmpfd);
	dup2(outfd, 1);
	close(outfd);
	FT_TAP_IEQ(t, err, 0);
	FT_TAP_OK(t, lst == NULL);
	FT_TAP_SEQ(t, buf, "hello world$\nhello world$\n");
	sh_env_end(&env);
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_empty);
	FT_TAP_TEST(t, test_singleton);
	FT_TAP_TEST(t, test_multiple);
}
