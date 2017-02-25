/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 15:08:52 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/25 17:35:02 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_SHELL_H
# define SH_SHELL_H

/*
** Functions composing the main flow of the prompt shell
*/

# include "sh_env.h"

/*
** Default environment variables
*/
# define SH_DEFAULT_PATH "/usr/sbin:/usr/bin:/sbin:/bin"
# define SH_DEFAULT_PS1 "$ "

/*
** Initialize the shell environment
**
** Returns 0 if successful, -1 on error.
*/
int		sh_shell_start(t_sh_env *env, char *const envp[]);

/*
** Prompt the user and execute the input
**
** Returns 0 if the program should continue, -1 if it should stop.
*/
int		sh_shell_prompt(t_sh_env *env);

/*
** Clear memory at the end of the program
**
** Returns the exit status of the shell.
** Should not be called if sh_shell_start failed.
*/
int		sh_shell_end(t_sh_env *env);

#endif
