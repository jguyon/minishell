/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_files.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 15:33:49 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/27 01:09:23 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_FILES_H
# define SH_FILES_H

/*
** Functions to manipulate files and paths
*/

# include <sys/stat.h>

/*
** Append path @child to @parent into @joined
**
** Returns 0 if successful, -1 if @child is absolute,
** the error number otherwise.
*/
int		sh_path_join(const char *parent, const char *child, char **joined);

/*
** Get the canonical form of path @path into @canon
**
** Returns 0 if successful, -1 if @path is not absolute
** the error number otherwise.
*/
int		sh_path_canonical(const char *path, char **canon);

/*
** Check if a directory is searchable
**
** Returns 0 if successful, the error number otherwise.
*/
int		sh_check_dir(const char *path);

#endif
