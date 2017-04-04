/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_files.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 15:33:49 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/04 13:05:29 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_FILES_H
# define SH_FILES_H

/*
** Functions to manipulate files and paths
*/

# include "sh_errors.h"
# include <sys/stat.h>

/*
** Append path @child to @parent into @joined
**
** /!\ @child must not begin with '/'
*/
t_err	sh_path_join(const char *parent, const char *child, char **joined);

/*
** Get the canonical form of path @path into @canon
**
** /!\ @path must begin with '/'
*/
t_err	sh_path_canonical(const char *path, char **canon);

/*
** Check if a directory is searchable
*/
t_err	sh_check_dir(const char *path);

/*
** Check if a file is executable
*/
t_err	sh_check_bin(const char *path);

#endif
