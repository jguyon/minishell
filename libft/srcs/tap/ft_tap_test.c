/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tap_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 23:30:58 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/28 18:45:48 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tap.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

static int	run_test(t_tap *t, void (*test)(t_tap *s))
{
	t_tap	sub;

	sub.nesting = t->nesting + 4;
	sub.plan = 0;
	sub.run = 0;
	sub.passed = 0;
	test(&sub);
	ft_tap_end(&sub);
	if (sub.passed != sub.run)
		return (0);
	else
		return (1);
}

static int	fork_test(t_tap *t, void (*test)(t_tap *s), const char *msg)
{
	pid_t	pid;
	int		stat;

	fflush(NULL);
	pid = fork();
	if (pid == 0)
		exit(run_test(t, test) ? 0 : 1);
	else if (pid == -1)
		ft_tap_fail(t, msg);
	else
	{
		waitpid(pid, &stat, 0);
		if (WIFEXITED(stat) && WEXITSTATUS(stat) == 0)
			ft_tap_pass(t, msg);
		else
			ft_tap_fail(t, msg);
		return (WIFEXITED(stat) && WEXITSTATUS(stat) == 0 ? 1 : 0);
	}
	return (0);
}

int			ft_tap_test(t_tap *t, void (*test)(t_tap *s), const char *msg)
{
	if (!msg)
		msg = "passes";
	printf("%*s# Subtest: %s\n", (int)t->nesting, "", msg);
	return (fork_test(t, test, msg));
}
