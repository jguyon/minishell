/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_check_bin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 15:18:02 by jguyon            #+#    #+#             */
/*   Updated: 2017/05/04 17:38:02 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_files.h"
#include "ft_debug.h"
#include <unistd.h>

t_sh_err	sh_check_bin(const char *path)
{
	struct stat	st;

	FT_ASSERT(path != NULL);
	if (access(path, F_OK))
		return (SH_ERR_NOENT);
	if (stat(path, &st))
		return (SH_ERR_IO);
	if (!S_ISREG(st.st_mode))
		return (SH_ERR_NOTREG);
	if (access(path, X_OK))
		return (SH_ERR_NOPERM);
	return (SH_ERR_OK);
}
