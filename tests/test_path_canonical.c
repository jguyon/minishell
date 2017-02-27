/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_path_canonical.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 18:04:32 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/27 12:03:21 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "sh_files.h"
#include <stdlib.h>
#include <stdio.h>

static void	test_dotdot(t_tap *t)
{
	char	*canon;

	mkdir("/tmp/sh_sub", S_IRWXU);
	mkdir("/tmp/sh_dir", S_IRWXU);
	FT_TAP_IEQ(t, sh_path_canonical("/tmp/..", &canon), 0);
	FT_TAP_SEQ(t, canon, "/");
	free(canon);
	FT_TAP_IEQ(t, sh_path_canonical("/tmp/sh_sub/../sh_dir/", &canon), 0);
	FT_TAP_SEQ(t, canon, "/tmp/sh_dir");
	free(canon);
	remove("/tmp/sh_sub");
	remove("/tmp/sh_dir");
}

static void	test_trailing_dotdot(t_tap *t)
{
	char	*canon;

	mkdir("/tmp/sh_some", S_IRWXU);
	mkdir("/tmp/sh_some/sh_sub", S_IRWXU);
	FT_TAP_IEQ(t, sh_path_canonical("/tmp/sh_some/sh_sub/..", &canon), 0);
	FT_TAP_SEQ(t, canon, "/tmp/sh_some");
	free(canon);
	FT_TAP_IEQ(t, sh_path_canonical("/tmp/sh_some/sh_sub/../", &canon), 0);
	FT_TAP_SEQ(t, canon, "/tmp/sh_some");
	free(canon);
	remove("/tmp/sh_some/sh_sub");
	remove("/tmp/sh_some");
}

static void	test_leading_dotdot(t_tap *t)
{
	char	*canon;

	mkdir("/tmp/sh_dir", S_IRWXU);
	FT_TAP_IEQ(t, sh_path_canonical("/../tmp/sh_dir", &canon), 0);
	FT_TAP_SEQ(t, canon, "/tmp/sh_dir");
	free(canon);
	FT_TAP_IEQ(t, sh_path_canonical("/../tmp/sh_dir/", &canon), 0);
	FT_TAP_SEQ(t, canon, "/tmp/sh_dir");
	free(canon);
	remove("/tmp/sh_dir");
}

static void	test_onedot(t_tap *t)
{
	char	*canon;

	mkdir("/tmp/sh_sub", S_IRWXU);
	mkdir("/tmp/sh_sub/sh_dir", S_IRWXU);
	FT_TAP_IEQ(t, sh_path_canonical("/tmp/sh_sub/./sh_dir", &canon), 0);
	FT_TAP_SEQ(t, canon, "/tmp/sh_sub/sh_dir");
	free(canon);
	FT_TAP_IEQ(t, sh_path_canonical("/tmp/sh_sub/./sh_dir/", &canon), 0);
	FT_TAP_SEQ(t, canon, "/tmp/sh_sub/sh_dir");
	free(canon);
	remove("/tmp/sh_sub");
	remove("/tmp/sh_sub/sh_dir");
}

static void	test_trailing_onedot(t_tap *t)
{
	char	*canon;

	mkdir("/tmp/sh_some", S_IRWXU);
	mkdir("/tmp/sh_some/sh_sub", S_IRWXU);
	FT_TAP_IEQ(t, sh_path_canonical("/tmp/sh_some/sh_sub/.", &canon), 0);
	FT_TAP_SEQ(t, canon, "/tmp/sh_some/sh_sub");
	free(canon);
	FT_TAP_IEQ(t, sh_path_canonical("/tmp/sh_some/sh_sub/.", &canon), 0);
	FT_TAP_SEQ(t, canon, "/tmp/sh_some/sh_sub");
	free(canon);
	remove("/tmp/sh_some/sh_sub");
	remove("/tmp/sh_some");
}

static void	test_leading_onedot(t_tap *t)
{
	char	*canon;

	mkdir("/tmp/sh_dir", S_IRWXU);
	FT_TAP_IEQ(t, sh_path_canonical("/./tmp/sh_dir", &canon), 0);
	FT_TAP_SEQ(t, canon, "/tmp/sh_dir");
	free(canon);
	FT_TAP_IEQ(t, sh_path_canonical("/./tmp/sh_dir/", &canon), 0);
	FT_TAP_SEQ(t, canon, "/tmp/sh_dir");
	free(canon);
	remove("/tmp/sh_dir");
}

static void	test_empty(t_tap *t)
{
	char	*canon;

	mkdir("/tmp/sh_sub", S_IRWXU);
	mkdir("/tmp/sh_sub/sh_dir", S_IRWXU);
	FT_TAP_IEQ(t, sh_path_canonical("/tmp/sh_sub//sh_dir", &canon), 0);
	FT_TAP_SEQ(t, canon, "/tmp/sh_sub/sh_dir");
	free(canon);
	FT_TAP_IEQ(t, sh_path_canonical("/tmp/sh_sub//sh_dir/", &canon), 0);
	FT_TAP_SEQ(t, canon, "/tmp/sh_sub/sh_dir");
	free(canon);
	remove("/tmp/sh_sub/sh_dir");
	remove("/tmp/sh_sub");
}

static void	test_trailing_empty(t_tap *t)
{
	char	*canon;

	mkdir("/tmp/sh_some", S_IRWXU);
	mkdir("/tmp/sh_some/sh_sub", S_IRWXU);
	FT_TAP_IEQ(t, sh_path_canonical("/tmp/sh_some/sh_sub//", &canon), 0);
	FT_TAP_SEQ(t, canon, "/tmp/sh_some/sh_sub");
	free(canon);
	FT_TAP_IEQ(t, sh_path_canonical("/tmp/sh_some/sh_sub//", &canon), 0);
	FT_TAP_SEQ(t, canon, "/tmp/sh_some/sh_sub");
	free(canon);
	remove("/tmp/sh_some/sh_sub");
	remove("/tmp/sh_some");
}

static void	test_leading_empty(t_tap *t)
{
	char	*canon;

	mkdir("/tmp/sh_dir", S_IRWXU);
	FT_TAP_IEQ(t, sh_path_canonical("//tmp/sh_dir", &canon), 0);
	FT_TAP_SEQ(t, canon, "/tmp/sh_dir");
	free(canon);
	FT_TAP_IEQ(t, sh_path_canonical("//tmp/sh_dir/", &canon), 0);
	FT_TAP_SEQ(t, canon, "/tmp/sh_dir");
	free(canon);
	remove("/tmp/sh_dir");
}

static void	test_mixed(t_tap *t)
{
	char	*canon;

	mkdir("/tmp/sh_sub", S_IRWXU);
	mkdir("/tmp/sh_dir", S_IRWXU);
	FT_TAP_IEQ(t, sh_path_canonical("/tmp/sh_sub/./.././///sh_dir/./", &canon), 0);
	FT_TAP_SEQ(t, canon, "/tmp/sh_dir");
	free(canon);
	FT_TAP_IEQ(t, sh_path_canonical("///////../../../././.././///", &canon), 0);
	FT_TAP_SEQ(t, canon, "/");
	free(canon);
	remove("/tmp/sh_sub");
	remove("/tmp/sh_dir");
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_dotdot);
	FT_TAP_TEST(t, test_trailing_dotdot);
	FT_TAP_TEST(t, test_leading_dotdot);
	FT_TAP_TEST(t, test_onedot);
	FT_TAP_TEST(t, test_trailing_onedot);
	FT_TAP_TEST(t, test_leading_onedot);
	FT_TAP_TEST(t, test_empty);
	FT_TAP_TEST(t, test_trailing_empty);
	FT_TAP_TEST(t, test_leading_empty);
	FT_TAP_TEST(t, test_mixed);
}
