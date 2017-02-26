/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_path_canonical.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 18:04:32 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/26 18:47:27 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "sh_files.h"
#include <stdlib.h>

static void	test_dotdot(t_tap *t)
{
	char	*canon;

	FT_TAP_IEQ(t, sh_path_canonical("/some/sub/../dir", &canon), 0);
	FT_TAP_SEQ(t, canon, "/some/dir");
	free(canon);
	FT_TAP_IEQ(t, sh_path_canonical("/some/sub/../dir/", &canon), 0);
	FT_TAP_SEQ(t, canon, "/some/dir");
	free(canon);
}

static void	test_trailing_dotdot(t_tap *t)
{
	char	*canon;

	FT_TAP_IEQ(t, sh_path_canonical("/some/few/sub/..", &canon), 0);
	FT_TAP_SEQ(t, canon, "/some/few");
	free(canon);
	FT_TAP_IEQ(t, sh_path_canonical("/some/few/sub/../", &canon), 0);
	FT_TAP_SEQ(t, canon, "/some/few");
	free(canon);
}

static void	test_leading_dotdot(t_tap *t)
{
	char	*canon;

	FT_TAP_IEQ(t, sh_path_canonical("/../some/dir", &canon), 0);
	FT_TAP_SEQ(t, canon, "/some/dir");
	free(canon);
	FT_TAP_IEQ(t, sh_path_canonical("/../some/dir/", &canon), 0);
	FT_TAP_SEQ(t, canon, "/some/dir");
	free(canon);
}

static void	test_onedot(t_tap *t)
{
	char	*canon;

	FT_TAP_IEQ(t, sh_path_canonical("/some/sub/./dir", &canon), 0);
	FT_TAP_SEQ(t, canon, "/some/sub/dir");
	free(canon);
	FT_TAP_IEQ(t, sh_path_canonical("/some/sub/./dir/", &canon), 0);
	FT_TAP_SEQ(t, canon, "/some/sub/dir");
	free(canon);
}

static void	test_trailing_onedot(t_tap *t)
{
	char	*canon;

	FT_TAP_IEQ(t, sh_path_canonical("/some/few/sub/.", &canon), 0);
	FT_TAP_SEQ(t, canon, "/some/few/sub");
	free(canon);
	FT_TAP_IEQ(t, sh_path_canonical("/some/few/sub/.", &canon), 0);
	FT_TAP_SEQ(t, canon, "/some/few/sub");
	free(canon);
}

static void	test_leading_onedot(t_tap *t)
{
	char	*canon;

	FT_TAP_IEQ(t, sh_path_canonical("/./some/dir", &canon), 0);
	FT_TAP_SEQ(t, canon, "/some/dir");
	free(canon);
	FT_TAP_IEQ(t, sh_path_canonical("/./some/dir/", &canon), 0);
	FT_TAP_SEQ(t, canon, "/some/dir");
	free(canon);
}

static void	test_empty(t_tap *t)
{
	char	*canon;

	FT_TAP_IEQ(t, sh_path_canonical("/some/sub//dir", &canon), 0);
	FT_TAP_SEQ(t, canon, "/some/sub/dir");
	free(canon);
	FT_TAP_IEQ(t, sh_path_canonical("/some/sub//dir/", &canon), 0);
	FT_TAP_SEQ(t, canon, "/some/sub/dir");
	free(canon);
}

static void	test_trailing_empty(t_tap *t)
{
	char	*canon;

	FT_TAP_IEQ(t, sh_path_canonical("/some/few/sub//", &canon), 0);
	FT_TAP_SEQ(t, canon, "/some/few/sub");
	free(canon);
	FT_TAP_IEQ(t, sh_path_canonical("/some/few/sub//", &canon), 0);
	FT_TAP_SEQ(t, canon, "/some/few/sub");
	free(canon);
}

static void	test_leading_empty(t_tap *t)
{
	char	*canon;

	FT_TAP_IEQ(t, sh_path_canonical("//some/dir", &canon), 0);
	FT_TAP_SEQ(t, canon, "/some/dir");
	free(canon);
	FT_TAP_IEQ(t, sh_path_canonical("//some/dir/", &canon), 0);
	FT_TAP_SEQ(t, canon, "/some/dir");
	free(canon);
}

static void	test_mixed(t_tap *t)
{
	char	*canon;

	FT_TAP_IEQ(t, sh_path_canonical("/some/sub/./.././///dir/./", &canon), 0);
	FT_TAP_SEQ(t, canon, "/some/dir");
	free(canon);
	FT_TAP_IEQ(t, sh_path_canonical("///////../../../././.././///", &canon), 0);
	FT_TAP_SEQ(t, canon, "/");
	free(canon);
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
