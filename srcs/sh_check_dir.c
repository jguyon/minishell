/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_check_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 00:58:51 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/27 01:18:17 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_files.h"
#include "sh_errors.h"
#include <unistd.h>

int		sh_check_dir(const char *path)
{
	struct stat	st;

	if (!access(path, X_OK))
		return (0);
	if (!stat(path, &st) && !S_ISDIR(st.st_mode))
		return (SH_ERR_NOTDIR);
	if (access(path, F_OK))
		return (SH_ERR_NOENT);
	return (SH_ERR_NOPERM);
}
