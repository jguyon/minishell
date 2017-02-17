/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_errors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 19:11:36 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/17 15:43:24 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ERRORS_H
# define MS_ERRORS_H

/*
** Error codes
*/
# define MS_ERR_NOMEM		1
# define MS_ERR_NOTFOUND	2
# define MS_ERR_PERM		3
# define MS_ERR_NOEXEC		4

/*
** Max error code, needs to be updated when adding new errors
*/
# define MS_ERR_MAX 4

/*
** Print an error message to stderr
** @status: if non-zero, program will exit with this status code
** @errnum: if non-zero, will print the message associated with the number
** @format: if non-null, will call printf with it and the following args
*/
void	ms_error(int status, int errnum, const char *format, ...);

#endif
