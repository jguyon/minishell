/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 16:57:55 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/18 23:07:53 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_program.h"
#include "ft_printf.h"
#include "ft_strings.h"
#include "ft_chars.h"

#define OPTERR(c) "illegal option -- %c", c
#define ARGERR(c) "option requires an argument -- %c", c
#define IS_OPT_START(str) (str && str[0] == '-' && str[1] && str[1] != '-')
#define IS_OPT_END(str) (str && str[0] == '-' && str[1] == '-' && !str[2])
#define MISSING_OPT '?'
#define ARG_INDICATOR ':'
#define IS_VALID_OPT(c) ft_isalnum(c)
#define ERR_OPT 1
#define ERR_ARG 2

char		*g_ft_optarg = NULL;

int			g_ft_opterr = 1;

int			g_ft_optind = 1;

int			g_ft_optopt = 0;

static char	*next_option(int argc, char *const argv[])
{
	static int	curr_index = 0;
	static char	*curr_char = NULL;

	if (g_ft_optind < 1 || g_ft_optind != curr_index || !curr_char)
	{
		if (g_ft_optind < 1)
			g_ft_optind = 1;
		curr_char = g_ft_optind < argc ? argv[g_ft_optind] : NULL;
		if (!IS_OPT_START(curr_char))
		{
			if (IS_OPT_END(curr_char))
				++g_ft_optind;
			return (NULL);
		}
		curr_index = g_ft_optind;
	}
	++curr_char;
	return (curr_char);
}

static int	missing(int err, char opt, const char *optstring)
{
	if (optstring[0] == ARG_INDICATOR)
	{
		if (err == ERR_OPT)
			return (MISSING_OPT);
		else if (err == ERR_ARG)
			return (ARG_INDICATOR);
	}
	if (g_ft_opterr)
	{
		if (err == ERR_OPT)
			ft_error(0, 0, OPTERR(opt));
		else if (err == ERR_ARG)
			ft_error(0, 0, ARGERR(opt));
	}
	return (MISSING_OPT);
}

int			ft_getopt(int argc, char *const argv[], const char *optstring)
{
	char	*argvopt;
	char	*stropt;

	if (!(argvopt = next_option(argc, argv)))
		return (-1);
	g_ft_optopt = *argvopt;
	if (*(argvopt + 1) == '\0')
		++g_ft_optind;
	if (!IS_VALID_OPT(*argvopt) || !(stropt = ft_strchr(optstring, *argvopt)))
		return (missing(ERR_OPT, *argvopt, optstring));
	if (*(stropt + 1) == ARG_INDICATOR)
	{
		if (*(argvopt + 1) == '\0')
			g_ft_optarg = argv[g_ft_optind];
		else
			g_ft_optarg = argvopt + 1;
		++g_ft_optind;
		if (g_ft_optind > argc)
		{
			g_ft_optind = argc;
			return (missing(ERR_ARG, g_ft_optopt, optstring));
		}
	}
	return (g_ft_optopt);
}
