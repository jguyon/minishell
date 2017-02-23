/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_errors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 15:19:37 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/23 16:03:22 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_ERRORS_H
# define SH_ERRORS_H

/*
** Errors needed by the program
**
** Meant to be used with ft_error.
*/

/*
** Error numbers
*/
# define SH_ERR_NOMEM		1
# define SH_ERR_IO			2

/*
** Get the error message corresponding to an error number
**
** Returns NULL if the error is unknown, or the error string.
** The returned string should not be freed.
*/
char	*sh_strerror(int errnum);

#endif
