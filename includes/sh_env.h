/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 16:23:40 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/24 02:04:08 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_ENV_H
# define SH_ENV_H

# include "ft_darrays.h"
# include "ft_strings.h"

typedef struct	s_sh_env {
	int			exit_status;
	int			should_exit;
	t_darray	vars;
}				t_sh_env;

# define SH_ENV_NAMLEN(var) ((size_t)(ft_strchrnul(var, '=') - (var)))

int				sh_env_start(t_sh_env *env, char *const envp[]);
void			sh_env_end(t_sh_env *env);
char *const		*sh_env_vars(t_sh_env *env);
const char		*sh_env_getvar(t_sh_env *env, const char *name);
int				sh_env_setvar(t_sh_env *env, const char *name, const char *val);
void			sh_env_unsetvar(t_sh_env *env, const char *name);

typedef struct	s_sh_builtin {
	const char	*name;
	int			(*fn)(int ac, char *const av[], t_sh_env *env);
}				t_sh_builtin;

# define SH_EXIT_SUCCESS	0
# define SH_EXIT_NOFORK		125
# define SH_EXIT_NOEXEC		126
# define SH_EXIT_NOTFOUND	127
# define SH_EXIT_SIGNAL		128

# define SH_EXIT_STATUS(status) (status & 0xFF)

int				sh_env_binpath(t_sh_env *env, const char *name, char **path);
int				sh_env_builtin(t_sh_env *env, const char *name,
					t_sh_builtin **builtin);
int				sh_env_exec_bin(t_sh_env *env, const char *path,
					char *const argv[]);
int				sh_env_exec_builtin(t_sh_env *env, t_sh_builtin *builtin,
					char *const argv[]);

int				sh_env_exec(t_sh_env *env, char *const argv[]);
void			sh_env_exit(t_sh_env *env, int status);
int				sh_env_should_exit(t_sh_env *env);
int				sh_env_status(t_sh_env *env);

#endif
