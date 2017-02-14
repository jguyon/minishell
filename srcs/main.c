/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 15:15:12 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/14 19:52:36 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_program.h"
#include "ft_streams.h"
#include "ft_strings.h"
#include <unistd.h>

int		main(int ac, char **av, char **envp)
{
	char	cmd[LINE_MAX + 1];
	pid_t	pid;
	char	*argv[2];

	(void)av;
	(void)ac;
	ft_setvbuf(FT_STDOUT, NULL, FT_IONBF, 0);
	argv[0] = cmd;
	argv[1] = NULL;
	while (!ft_fputs("$> ", FT_STDOUT) && ft_fgets(cmd, sizeof(cmd), FT_STDIN))
	{
		if (ft_feof(FT_STDIN))
		{
			ft_clearerr(FT_STDIN);
			ft_fputc('\n', FT_STDOUT);
		}
		cmd[ft_strchrnul(cmd, '\n') - cmd] = '\0';
		if ((pid = fork()) < 0)
			break ;
		else if (pid > 0)
			wait(&pid);
		else if (execve(cmd, argv, envp))
			ft_exit(FT_EXIT_FAILURE);
	}
	return (ft_cleanup(FT_EXIT_SUCCESS));
}
