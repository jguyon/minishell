/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 16:23:40 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/04 12:58:08 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_ENV_H
# define SH_ENV_H

/*
** Functions for managing the whole shell environment
*/

# include "sh_errors.h"
# include "ft_darrays.h"
# include "ft_strings.h"

/*
** Get the length of the variable name in a string of type "NAME=value"
*/
# define SH_ENV_NAMLEN(var) ((size_t)(ft_strchrnul((var), '=') - (var)))

/*
** Exit statuses of commands on success and on specific errors
**
** Not to be confused with error *numbers* provided in sh_errors.
*/
# define SH_EXIT_SUCCESS	0
# define SH_EXIT_NOFORK		125
# define SH_EXIT_NOEXEC		126
# define SH_EXIT_NOTFOUND	127
# define SH_EXIT_SIGNAL		128

/*
** Keep only one byte of the exit status
*/
# define SH_EXIT_STATUS(status) (status & 0xFF)

/*
** Type representing the shell environment
*/
typedef struct	s_sh_env {
	int			exit_status;
	int			should_exit;
	t_darray	vars;
	char		*cwd;
}				t_sh_env;

/*
** Type representing a built-in util
*/
typedef struct	s_sh_builtin {
	const char	*name;
	int			(*fn)(int ac, char *const av[], t_sh_env *env);
}				t_sh_builtin;

/*
** Init @env with the system environment @envp
*/
t_err			sh_env_start(t_sh_env *env, char *const envp[]);

/*
** Clear @env when it is not needed anymore
*/
void			sh_env_end(t_sh_env *env);

/*
** Get the null-terminated array of environment variables
*/
char *const		*sh_env_vars(t_sh_env *env);

/*
** Get the value of the environment variable @name
**
** Returns NULL if it was not found.
*/
const char		*sh_env_getvar(t_sh_env *env, const char *name);

/*
** Set the value of the environment variable @name to @val
**
** If @name contains '=', the variable name will stop before it.
** If @val is NULL and @name is formatted like "NAME=value",
** the variable "NAME" will be assigned "value".
*/
t_err			sh_env_setvar(t_sh_env *env, const char *name, const char *val);

/*
** Unset the environment variable @name
**
** Does nothing special if the variable is not found.
*/
void			sh_env_unsetvar(t_sh_env *env, const char *name);

/*
** Get the current working directory
*/
t_err			sh_env_getcwd(t_sh_env *env, int nosym, char **cwd);

/*
** Change the current working directory
*/
t_err			sh_env_chdir(t_sh_env *env, const char *path, int nosym);

/*
** Execute the command provided by @argv
**
** Will search for a built-in or an executable in the PATH.
** Will store its exit status in @env.
*/
t_err			sh_env_exec(t_sh_env *env, char *const argv[]);

/*
** Mark the env for exit with @status
**
** If @status is negative, will take the status of the last command.
*/
void			sh_env_exit(t_sh_env *env, int status);

/*
** Check if the env is marked for exit
*/
int				sh_env_should_exit(t_sh_env *env);

/*
** Get the status that the shell should exit with
*/
int				sh_env_status(t_sh_env *env);

/*
** Search for an executable in the PATH and store it in @path
**
** You should free @path once you are finished with it.
*/
t_err			sh_env_binpath(t_sh_env *env, const char *name, char **path);

/*
** Search for a built-in and store it in @builtin
**
** @builtin should not be freed.
*/
t_err			sh_env_builtin(t_sh_env *env, const char *name,
					t_sh_builtin **builtin);

/*
** Execute the executable pointed to by @path
**
** Returns the exit code of the executed program.
*/
int				sh_env_exec_bin(t_sh_env *env, const char *path,
					char *const argv[]);

/*
** Executable the built-in @builtin
**
** Returns the exit code of the executed builtin.
*/
int				sh_env_exec_builtin(t_sh_env *env, t_sh_builtin *builtin,
					char *const argv[]);

#endif
