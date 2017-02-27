/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_check_bin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 15:18:02 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/27 16:07:28 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_files.h"
#include "sh_errors.h"
#include <unistd.h>

int		sh_check_bin(const char *path)
{
	struct stat	st;

	if (access(path, F_OK))
		return (SH_ERR_NOENT);
	if (stat(path, &st))
		return (SH_ERR_IO);
	if (!S_ISREG(st.st_mode))
		return (SH_ERR_NOTREG);
	if (access(path, X_OK))
		return (SH_ERR_NOPERM);
	return (0);
}
