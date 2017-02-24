/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmd_toargv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 22:27:10 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/24 23:42:58 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_ast.h"
#include "ft_darrays.h"
#include "ft_memory.h"

static int	set_arg(t_darray *argv, size_t i, char *str)
{
	if (ft_darr_set(argv, i, &str))
	{
		ft_memdel((void **)&str);
		return (-1);
	}
	return (0);
}

static void	del_argv(t_darray *argv)
{
	size_t	i;
	char	*arg;

	i = 0;
	ft_darr_get(argv, i, &arg);
	while (arg)
	{
		ft_memdel((void **)(&arg));
		++i;
		ft_darr_get(argv, i, &arg);
	}
	ft_darr_clear(argv);
}

char		**sh_cmd_toargv(t_sh_cmd **cmd)
{
	t_darray		dargv;
	size_t			i;
	t_dlist_node	*node;
	t_sh_word		*arg;
	int				err;

	if (!(*cmd))
		return (NULL);
	if (!(err = ft_darr_init(&dargv, NULL, sizeof(char *), 8))
		&& !(err = set_arg(&dargv, 0, sh_word_tostr(&((*cmd)->name)))))
	{
		i = 1;
		while ((node = ft_dlst_popl(&((*cmd)->args))))
		{
			arg = FT_DLST_ENTRY(&((*cmd)->args), node);
			if ((err = set_arg(&dargv, i, sh_word_tostr(&arg))))
				break ;
			++i;
		}
	}
	sh_cmd_del(cmd);
	if (!err && !set_arg(&dargv, i, NULL))
		return (dargv.array);
	del_argv(&dargv);
	return (NULL);
}
