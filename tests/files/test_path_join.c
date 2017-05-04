/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_path_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 15:59:38 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/04 12:37:35 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "sh_files.h"
#include <stdlib.h>

void		test_nonempty_parent(t_tap *t)
{
	char	*joined;

	FT_TAP_IEQ(t, sh_path_join("some/dir", "child/dir", &joined), 0);
	FT_TAP_SEQ(t, joined, "some/dir/child/dir");
	free(joined);
}

void		test_root_parent(t_tap *t)
{
	char	*joined;

	FT_TAP_IEQ(t, sh_path_join("/", "child/dir/", &joined), 0);
	FT_TAP_SEQ(t, joined, "/child/dir/");
	free(joined);
}

void		test_empty_parent(t_tap *t)
{
	char	*joined;

	FT_TAP_IEQ(t, sh_path_join("", "child/dir", &joined), 0);
	FT_TAP_SEQ(t, joined, "./child/dir");
	free(joined);
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_nonempty_parent);
	FT_TAP_TEST(t, test_root_parent);
	FT_TAP_TEST(t, test_empty_parent);
}
