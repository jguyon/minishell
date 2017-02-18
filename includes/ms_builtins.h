/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 12:44:58 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/18 14:14:31 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_BUILTINS_H
# define MS_BUILTINS_H

# include "ms_env.h"

typedef int	(*t_builtin)(int ac, char *av[], t_env *env);

int			ms_builtin_cd(int ac, char *av[], t_env *env);
int			ms_builtin_pwd(int ac, char *av[], t_env *env);
int			ms_builtin_env(int ac, char *av[], t_env *env);

#endif
