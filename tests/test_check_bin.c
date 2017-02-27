/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_check_bin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 15:48:52 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/27 19:13:09 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "sh_files.h"
#include "sh_errors.h"
#include <stdio.h>
#include <fcntl.h>

static void	test_success(t_tap *t)
{
	creat("/tmp/sh_exe", S_IXUSR);
	FT_TAP_IEQ(t, sh_check_bin("/tmp/sh_exe"), 0);
	remove("/tmp/sh_exe");
}

static void	test_notfile(t_tap *t)
{
	mkdir("/tmp/sh_exe_notfile", S_IXUSR);
	FT_TAP_IEQ(t, sh_check_bin("/tmp/sh_exe_notfile"), SH_ERR_NOTREG);
	remove("/tmp/sh_exe_notfile");
}

static void	test_noent(t_tap *t)
{
	FT_TAP_IEQ(t, sh_check_bin("/tmp/sh_exe_noent"), SH_ERR_NOENT);
}

static void	test_noperm(t_tap *t)
{
	creat("/tmp/sh_exe_noperm", 0);
	FT_TAP_IEQ(t, sh_check_bin("/tmp/sh_exe_noperm"), SH_ERR_NOPERM);
	remove("/tmp/sh_exe_noperm");
}

void		run_tests(t_tap *t)
{
	FT_TAP_TEST(t, test_success);
	FT_TAP_TEST(t, test_notfile);
	FT_TAP_TEST(t, test_noent);
	FT_TAP_TEST(t, test_noperm);
}
