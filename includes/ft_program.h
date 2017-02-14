/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_program.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 17:18:15 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/14 12:17:42 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PROGRAM_H
# define FT_PROGRAM_H

/*
** Functions for managing program lifecycle
*/

# include <stdlib.h>
# include <limits.h>

/*
** FT_EXIT_SUCCESS, FT_EXIT_FAILURE - portable exit statuses
*/
# define FT_EXIT_SUCCESS EXIT_SUCCESS
# define FT_EXIT_FAILURE EXIT_FAILURE

/*
** FT_ONEXIT_MAX - max number of exit callbacks
*/
# define FT_ONEXIT_MAX 32

/*
** ft_onexit - register a callback to be called before exit
** @fn: function to call with the exit status and @arg
** @arg: value to pass to @fn
**
** Returns 0 if successful, some non-zero value otherwise.
*/
int				ft_onexit(void (*fn)(int, void *), void *arg);

/*
** ft_cleanup - execute all exit callbacks
** @status: exit status of the program
**
** Returns @status to allow calling the function in the return
** of the main function.
*/
int				ft_cleanup(int status);

/*
** ft_exit - execute all exit callbacks and actually exit
** @status: exit status of the program
*/
void			ft_exit(int status);

/*
** Private array containing the registered callbacks
*/

typedef struct	s_exit_cb {
	void	*arg;
	void	(*fn)(int status, void *arg);
}				t_exit_cb;

t_exit_cb		g_exit_cb[FT_ONEXIT_MAX];

/*
** ft_setprogname - set the program name to the last part of @progname
** @progname: invocation name of the program (argv[0])
*/
void			ft_setprogname(const char *progname);

/*
** ft_getprogname - get the program name
**
** Returns an empty string if ft_setprogname has not called before.
*/
const char		*ft_getprogname(void);

/*
** Private string holding the program name
*/
char			g_program_name[NAME_MAX + 1];

#endif
