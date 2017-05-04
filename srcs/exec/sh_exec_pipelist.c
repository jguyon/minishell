/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_pipelist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:02:34 by jguyon            #+#    #+#             */
/*   Updated: 2017/05/04 17:55:14 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_exec.h"
#include "ft_memory.h"
#include "ft_debug.h"

static t_sh_err	pipe_cmd(t_sh_env *env, t_sh_cmd **cmd,
					int fds[2], pid_t *child)
{
	t_sh_err	err;
	char		**argv;
	size_t		i;

	if (!(argv = sh_cmd_toargv(cmd)))
		return (SH_ERR_NOMEM);
	err = sh_env_pipe(env, argv, fds, child);
	i = 0;
	while (argv[i])
	{
		ft_strdel(&(argv[i]));
		++i;
	}
	ft_memdel((void **)&argv);
	return (err);
}

static void		close_fds(int fds[2])
{
	if (fds[0] != 0)
	{
		close(fds[0]);
		fds[0] = 0;
	}
	if (fds[1] != 1)
	{
		close(fds[1]);
		fds[1] = 1;
	}
}

static t_sh_err	pipe_fds(int fds[2])
{
	if (pipe(fds) == -1)
		return (SH_ERR_IO);
	return (SH_ERR_OK);
}

static t_sh_err	pipe_and_exec(t_sh_env *env, t_sh_pipelist *pipelst,
								int fdin)
{
	t_sh_cmd	*cmd;
	int			fds[2];
	int			pipefds[2];
	pid_t		pid;
	t_sh_err	err;

	err = SH_ERR_OK;
	fds[0] = fdin;
	fds[1] = 1;
	if ((cmd = sh_pipelist_pop(pipelst)))
	{
		if (!ft_dlst_empty(&(pipelst->cmds)) && !(err = pipe_fds(pipefds)))
			fds[1] = pipefds[1];
		err = err ? err : pipe_cmd(env, &cmd, fds, &pid);
		sh_cmd_del(&cmd);
		close_fds(fds);
		if (!ft_dlst_empty(&(pipelst->cmds)))
			err = err ? err : pipe_and_exec(env, pipelst, pipefds[0]);
		err = err ? err : sh_env_wait(env, pid);
	}
	close_fds(fds);
	return (err);
}

t_sh_err		sh_exec_pipelist(t_sh_env *env, t_sh_pipelist **pipe)
{
	t_sh_cmd	*cmd;
	t_sh_err	err;

	FT_ASSERT(env != NULL);
	FT_ASSERT(pipe != NULL);
	err = SH_ERR_OK;
	if (ft_dlst_singular(&((*pipe)->cmds)) || ft_dlst_empty(&((*pipe)->cmds)))
	{
		if ((cmd = sh_pipelist_pop(*pipe)))
			err = sh_exec_cmd(env, &cmd);
	}
	else
		err = pipe_and_exec(env, *pipe, 0);
	sh_pipelist_del(pipe);
	return (err);
}
