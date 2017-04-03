/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 22:58:58 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/13 22:46:41 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TAP_H
# define FT_TAP_H

/*
** Test library producing TAP output
**
** The TAP specification does not provide a way to format subtests.
** This library uses roughly the same format as node-tap, to be compatible
** with their formatters.
** The output is also compatible with the program prove, often available
** on *NIX platforms.
*/

# include <stddef.h>
# include <stdarg.h>
# include <inttypes.h>

# define DO_STR(token) #token
# define STR(token) DO_STR(token)

/*
** t_tap - type representing a test
*/
typedef struct	s_tap {
	size_t		nesting;
	size_t		plan;
	size_t		run;
	size_t		passed;
}				t_tap;

/*
** ft_tap_start, ft_tap_end - start and end a suite of tests
** @t: root test
*/
void			ft_tap_start(t_tap *t);
void			ft_tap_end(t_tap *t);

/*
** ft_tap_pass, ft_tap_fail - pass or fail a test
** @t: parent test
** @msg: message to print
*/
void			ft_tap_pass(t_tap *t, const char *msg);
void			ft_tap_fail(t_tap *t, const char *msg);

/*
** ft_tap_diag - print diagnostic information
** @t: parent test
** @args: default values passed before
** @rest: values
**
** @args and @rest should be formed by a null-terminated suite
** of key value pairs. A key is a string, A value is a format string followed
** by the arguments it needs.
*/
void			ft_tap_diag(t_tap *t, va_list args, ...);

/*
** FT_TAP_DIAG - default diagnostic info to pass to tests
*/
# define FT_TAP_DIAG "stack", "%s", __FILE__ ":" STR(__LINE__), NULL

/*
** ft_tap_quote - get a quoted version of a string
** to print as a diagnostic value
** @str: string to quote
*/
char			*ft_tap_quote(const char *str);

/*
** ft_tap_plan - plan for the number of assertions or subtests in a test
** @t: test
** @n: number of assertions
**
** Set to zero or do not call if you do not want to check the number of tests.
*/
void			ft_tap_plan(t_tap *t, size_t n);

/*
** Test macros and functions
**
** Macro variants of the functions provide default messages and
** diagnostic info. Use the functions when that is undesirable.
** Both the macros and the functions return whether the test was successful.
*/

/*
** ft_tap_test - create a subtest
** @t: parent test
** @test: test function
** @msg: name of the test
*/
int				ft_tap_test(t_tap *t, void (*test)(t_tap *s), const char *msg);

/*
** ft_tap_ok, ft_tap_notok - test truthyness
** @t: test
** @val: value to test
** @msg: message to print
** @rest: diagnostic key values
*/
int				ft_tap_ok(t_tap *t, int val, const char *msg, ...);
int				ft_tap_notok(t_tap *t, int val, const char *msg, ...);

/*
** ft_tap_ieq, ft_tap_notieq - test signed integer equality
** ft_tap_ueq, ft_tap_notueq - test unsigned integer equality
** ft_tap_seq, ft_tap_notseq - test string equality
** @t: test
** @actual: actual value
** @expected: expected value
** @msg: message to print
** @rest: diagnostic key values
*/
int				ft_tap_ieq(t_tap *t, intmax_t actual, intmax_t expected,
					const char *msg, ...);
int				ft_tap_notieq(t_tap *t, intmax_t actual, intmax_t expected,
					const char *msg, ...);
int				ft_tap_ueq(t_tap *t, uintmax_t actual, uintmax_t expected,
					const char *msg, ...);
int				ft_tap_notueq(t_tap *t, uintmax_t actual, uintmax_t expected,
					const char *msg, ...);
int				ft_tap_seq(t_tap *t, const char *actual, const char *expected,
					const char *msg, ...);
int				ft_tap_notseq(t_tap *t,
					const char *actual, const char *expected,
					const char *msg, ...);

/*
** FT_TAP_TEST - create a subtest
** @t: parent test
** @tst: test function
*/
# define FT_TAP_TEST(t, tst) ft_tap_test(t, &tst, #tst)

/*
** FT_TAP_OK, FT_TAP_NOTOK - test truthyness of an expression
** @t: current test
** @e: expression
*/
# define FT_TAP_OK(t, e) ft_tap_ok(t, e, #e" is true", FT_TAP_DIAG)
# define FT_TAP_NOTOK(t, e) ft_tap_notok(t, e, #e" is false", FT_TAP_DIAG)

/*
** FT_TAP_IEQ, FT_TAP_NOTIEQ - test equality between signed integers
** FT_TAP_UEQ, FT_TAP_NOTUEQ - test equality between unsigned integers
** FT_TAP_SEQ, FT_TAP_NOTSEQ - test equality between strings
** @t: current test
** @a: actual value
** @b: value to test against
*/
# define FT_TAP_IEQ(t, a, b) ft_tap_ieq(t, a, b, #a" == "#b, FT_TAP_DIAG)
# define FT_TAP_NOTIEQ(t, a, b) ft_tap_notieq(t, a, b, #a" != "#b, FT_TAP_DIAG)
# define FT_TAP_UEQ(t, a, b) ft_tap_ueq(t, a, b, #a" == "#b, FT_TAP_DIAG)
# define FT_TAP_NOTUEQ(t, a, b) ft_tap_notueq(t, a, b, #a" != "#b, FT_TAP_DIAG)
# define FT_TAP_SEQ(t, a, b) ft_tap_seq(t, a, b, #a" == "#b, FT_TAP_DIAG)
# define FT_TAP_NOTSEQ(t, a, b) ft_tap_notseq(t, a, b, #a" != "#b, FT_TAP_DIAG)

#endif
