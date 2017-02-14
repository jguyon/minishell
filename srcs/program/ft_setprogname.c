/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setprogname.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 19:58:39 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/14 12:19:41 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_program.h"
#include "ft_strings.h"

char	g_program_name[NAME_MAX + 1];

void	ft_setprogname(const char *progname)
{
	const char	*name;

	if ((name = ft_strrchr(progname, '/')))
		++name;
	else
		name = progname;
	ft_strncpy(g_program_name, name, NAME_MAX);
}
