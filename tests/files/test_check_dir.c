/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_check_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 01:10:26 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/27 16:04:42 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "sh_files.h"
#include "sh_errors.h"
#include <stdio.h>
#include <fcntl.h>

static void	test_success(t_tap *t)
{
	mkdir("/tmp/sh_dir", S_IXUSR);
	FT_TAP_IEQ(t, sh_check_dir("/tmp/sh_dir"), 0);
	remove("/tmp/sh_dir");
}

static void	test_notdir(t_tap *t)
{
	creat("/tmp/sh_dir_noexec", S_IXUSR);
	FT_TAP_IEQ(t, sh_check_dir("/tmp/sh_dir_noexec"), SH_ERR_NOTDIR);
	remove("/tmp/sh_dir_noexec");
}

static void	test_noent(t_tap *t)
{
	FT_TAP_IEQ(t, sh_check_dir("/tmp/sh_dir_noent"), SH_ERR_NOENT);
}

static void	test_noperm(t_tap *t)
{
	mkdir("/tmp/sh_dir_noperm", 0);
	FT_TAP_IEQ(t, sh_check_dir("/tmp/sh_dir_noperm"), SH_ERR_NOPERM);
	remove("/tmp/sh_dir_noperm");
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_success);
	FT_TAP_TEST(t, test_notdir);
	FT_TAP_TEST(t, test_noent);
	FT_TAP_TEST(t, test_noperm);
}
