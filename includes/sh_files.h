/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_files.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 15:33:49 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/26 16:55:01 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_FILES_H
# define SH_FILES_H

int		sh_path_join(const char *parent, const char *child, char **joined);
int		sh_path_canonical(const char *path, char **canon);

#endif
