/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 12:44:58 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/25 01:08:20 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_BUILTINS_H
# define MS_BUILTINS_H

# include "ms_env.h"

/*
** Change the working directory
**
** With no args, goes to HOME.
** With "-" arg, goes to previous directory.
*/
int			ms_builtin_cd(int ac, char *const av[], t_env *env);

/*
** Print the current working directory
*/
int			ms_builtin_pwd(int ac, char *const av[], t_env *env);

/*
** Set an environment variable
**
** Sets the variable given in the first argument to the value
** given in the second argument. If only one arg is given, sets
** the variable to an empty string.
*/
int			ms_builtin_setenv(int ac, char *const av[], t_env *env);

/*
** Unset an environment variable
*/
int			ms_builtin_unsetenv(int ac, char *const av[], t_env *env);

/*
** Execute a command in a modified environment
**
** With no args, prints the environment.
** Adds each KEY=value pairs to the environment before executing
** the specified command.
** With -i option, clears the environment before modifying it.
*/
int			ms_builtin_env(int ac, char *const av[], t_env *env);

#endif
