/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 00:19:00 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/04 13:02:24 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_EXEC_H
# define SH_EXEC_H

/*
** Interpret the shell language AST
*/

# include "sh_ast.h"
# include "sh_errors.h"
# include "sh_env.h"

/*
** Use @env to execute command @cmd
**
** @cmdname is set to the command name if possible, it should be freed.
*/
t_err	sh_exec_cmd(t_sh_env *env, t_sh_cmd *cmd, char **cmdname);

#endif
