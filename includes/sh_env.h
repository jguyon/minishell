/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 16:23:40 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/23 22:24:53 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_ENV_H
# define SH_ENV_H

# include "ft_darrays.h"
# include "ft_strings.h"

typedef struct	s_sh_env {
	t_darray	vars;
}				t_sh_env;

# define SH_ENV_NAMLEN(var) ((size_t)(ft_strchrnul(var, '=') - (var)))

int				sh_env_start(t_sh_env *env, char *const envp[]);
void			sh_env_end(t_sh_env *env);
char *const		*sh_env_vars(t_sh_env *env);
const char		*sh_env_getvar(t_sh_env *env, const char *name);
int				sh_env_setvar(t_sh_env *env, const char *name, const char *val);
void			sh_env_unsetvar(t_sh_env *env, const char *name);

int				sh_env_binpath(t_sh_env *env, const char *name, char **path);

#endif
