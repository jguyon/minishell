/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 12:44:58 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/25 02:22:02 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_BUILTINS_H
# define MS_BUILTINS_H

# include "ms_env.h"

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
