/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 12:44:58 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/21 23:12:50 by jguyon           ###   ########.fr       */
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
** Execute a command in a modified environment
**
** With no args, prints the environment.
** Adds each KEY=value pairs to the environment before executing
** the specified command.
** With -i option, clears the environment before modifying it.
*/
int			ms_builtin_env(int ac, char *const av[], t_env *env);

#endif
