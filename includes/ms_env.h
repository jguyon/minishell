/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 21:17:04 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/16 23:41:03 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ENV_H
# define MS_ENV_H

/*
** Utils to change the shell environment
*/

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
}				t_env;

/*
** Duplicate @envp into @env
*/
int				ms_env_start(t_env *env, char **envp);

/*
** Free memory allocated in @env
*/
void			ms_env_end(t_env *env);

/*
** Get the value of an environment variable
*/
const char		*ms_env_get(t_env *env, const char *name);

/*
** Set the value of an environment variable
*/
int				ms_env_set(t_env *env, const char *name, const char *value);

#endif