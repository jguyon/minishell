/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 12:44:58 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/21 18:21:16 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_BUILTINS_H
# define MS_BUILTINS_H

# include "ms_env.h"

/*
** Print the given arguments
**
** Separates arguments with spaces, ends with a newline unless
** '-n' is the first argument.
*/
int			ms_builtin_echo(int ac, char *const av[], t_env *env);

int			ms_builtin_cd(int ac, char *const av[], t_env *env);
int			ms_builtin_pwd(int ac, char *const av[], t_env *env);
int			ms_builtin_env(int ac, char *const av[], t_env *env);

#endif
