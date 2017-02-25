/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 01:06:44 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/25 02:30:10 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_BUILTINS_H
# define SH_BUILTINS_H

/*
** Built-in utilities
*/

# include "sh_env.h"

/*
** Print the given arguments
**
** Separates arguments with spaces, ends with a newline unless
** '-n' is the first argument.
*/
int			sh_builtin_echo(int ac, char *const av[], t_sh_env *env);

/*
** Change the working directory
**
** With no args, goes to HOME.
** With "-" arg, goes to previous directory.
*/
int			sh_builtin_cd(int ac, char *const av[], t_sh_env *env);

/*
** Print the current working directory
*/
int			sh_builtin_pwd(int ac, char *const av[], t_sh_env *env);

/*
** Set an environment variable
**
** Sets the variable given in the first argument to the value
** given in the second argument. If only one arg is given, sets
** the variable to an empty string.
*/
int			sh_builtin_setenv(int ac, char *const av[], t_sh_env *env);

/*
** Unset an environment variable
*/
int			sh_builtin_unsetenv(int ac, char *const av[], t_sh_env *env);

#endif
