/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 00:19:00 by jguyon            #+#    #+#             */
/*   Updated: 2017/05/04 17:54:09 by jguyon           ###   ########.fr       */
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
** Use @env to execute and free command @cmd
*/
t_sh_err	sh_exec_cmd(t_sh_env *env, t_sh_cmd **cmd);

/*
** Use @env to execute and free @pipe commands
*/
t_sh_err	sh_exec_pipelist(t_sh_env *env, t_sh_pipelist **pipe);

/*
** Use @env to execute and free @seqlist commands
*/
t_sh_err	sh_exec_seqlist(t_sh_env *env, t_sh_seqlist **lst);

#endif
