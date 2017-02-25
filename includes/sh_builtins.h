/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 01:06:44 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/25 01:08:17 by jguyon           ###   ########.fr       */
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

#endif
