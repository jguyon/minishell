/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_memstream.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 16:35:22 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/12 17:55:56 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_streams.h"
#include "ft_memory.h"

static ssize_t			write_ptr(void *cookie, const char *buff, size_t size)
{
	t_ptr_cookie	*p;
	char			*old;

	p = (t_ptr_cookie *)cookie;
	if (size >= p->fullsize - *(p->sizeloc))
	{
		while (size >= p->fullsize - *(p->sizeloc))
			p->fullsize = p->fullsize ? p->fullsize * 2 : 255;
		old = *(p->ptr);
		if (!(*(p->ptr) = ft_memalloc(p->fullsize + 1)))
			return (-1);
		ft_memcpy(*(p->ptr), old, *(p->sizeloc));
		ft_memdel((void **)&old);
	}
	ft_memcpy(*(p->ptr) + *(p->sizeloc), buff, size);
	*(p->sizeloc) += size;
	return (size);
}

static int				close_ptr(void *cookie)
{
	ft_memdel(&cookie);
	return (0);
}

static t_stream_funs	g_ptr_funs = {
	.write = &write_ptr,
	.close = &close_ptr,
};

t_stream				*ft_open_memstream(char **ptr, size_t *sizeloc)
{
	t_ptr_cookie	*p;

	if (!(p = ft_memalloc(sizeof(*p))))
		return (NULL);
	p->ptr = ptr;
	p->sizeloc = sizeloc;
	*(p->ptr) = NULL;
	*(p->sizeloc) = 0;
	return (ft_fopencookie(p, "w", g_ptr_funs));
}
