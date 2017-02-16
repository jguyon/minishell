/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_errors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 19:11:36 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/16 19:53:10 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ERRORS_H
# define MS_ERRORS_H

/*
** Error codes
*/
# define MS_ERR_CMDNOTFOUND	1

/*
** Max error code, needs to be updated when adding new errors
*/
# define MS_ERR_MAX 1

/*
** Print an error message to stderr
** @status: if non-zero, program will exit with this status code
** @errnum: if non-zero, will print the message associated with the number
** @format: if non-null, will call printf with it and the following args
*/
void	ms_error(int status, int errnum, const char *format, ...);

#endif
