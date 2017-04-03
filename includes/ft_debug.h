/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 11:42:02 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/03 11:34:16 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEBUG_H
# define FT_DEBUG_H

/*
** Debug utils
**
** FT_FEATURE_DEBUG needs to be previously defined for the macros not
** to be skipped.
** The easiest way to do that is to compile the lib with
** `make CPPFLAGS=-DFT_FEATURE_DEBUG` and compile your program
** with `clang -DFT_FEATURE_DEBUG`.
** Change the log file by defining FT_DEBUG_FILE to a path string
** (for example: `-DFT_FEATURE_FILE=\\\"/tmp/debug.log\\\"`).
*/

# include <stddef.h>

/*
** FT_DEBUG_FD - file descriptor for debug messages on the command line
*/
# ifndef FT_DEBUG_FD
#  define FT_DEBUG_FD 2
# endif

/*
** FT_DEBUG_FILE - path to write debug messages to
*/
# ifndef FT_DEBUG_FILE
#  define FT_DEBUG_FILE "/tmp/libftdebug.log"
# endif

/*
** FT_ASSERT_EXIT - exit status of the program for failed assertions
*/
# define FT_ASSERT_EXIT 2

/*
** FT_DEBUG - print a debug message
** @fmt: printf style format
** @...: format arguments
*/
void	ft_debug(const char *file, int line, const char *fmt, ...);
# ifdef FT_FEATURE_DEBUG
#  define FT_DEBUG(fmt, ...) ft_debug(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
# else
#  define FT_DEBUG(fmt, ...)
# endif

/*
** FT_ASSERT - exit program if a condition is not met
** @expr: expression to check
*/
void	ft_assert(const char *file, int line, const char *expr);
# ifdef FT_FEATURE_DEBUG
#  define FT_ASSERT(expr) ft_assert(__FILE__, __LINE__, (expr) ? NULL : #expr)
# else
#  define FT_ASSERT(expr)
# endif

#endif
