/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 21:17:04 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/17 21:16:55 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ENV_H
# define MS_ENV_H

/*
** Utils to change the shell environment
*/

# include "ft_dlists.h"
# include <stddef.h>

/*
** Check that @v is an assignment with name @n of length @l
*/
# define MS_ENV_ISVAR(v, n, l) (!ft_strncmp(v, n, l) && v[l] == '=')

/*
** Type to hold the environment
**
** @envp holds a null-terminated table of strings, this is what should be
** given as argument to functions that need the environment, like execve.
*/
typedef struct	s_env {
	char	**envp;
	size_t	size;
	size_t	alloc_size;
	t_dlist	bins;
}				t_env;

/*
** Type holding a path to an executable
**
** This is used for caching found binaries.
*/
typedef struct	s_bin {
	const char		*old_path;
	const char		*name;
	t_dlist_node	node;
	char			*file;
}				t_bin;

/*
** Duplicate @envp into @env
**
** Returns 0 if successful, -1 otherwise.
*/
int				ms_env_start(t_env *env, char **envp);

/*
** Free memory allocated in @env
*/
void			ms_env_end(t_env *env);

/*
** Get the value of an environment variable
**
** Returns NULL if not found.
*/
const char		*ms_env_get(t_env *env, const char *name);

/*
** Set the value of an environment variable
**
** Returns 0 if successful, -1 otherwise.
*/
int				ms_env_set(t_env *env, const char *name, const char *value);

/*
** Unset the value of an environment variable if it exists
**
** If not found, nothing special happens.
*/
void			ms_env_unset(t_env *env, const char *name);

/*
** Clear all values in the environment
*/
void			ms_env_clear(t_env *env);

/*
** Search in the PATH for a binary and return the resulting pathname
*/
char			*ms_resolve_bin(t_env *env, char *name);

#endif
