/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmemopen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 15:07:21 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/13 20:11:17 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_streams.h"
#include "ft_memory.h"

static ssize_t			write_mem(void *cookie, const char *buff, size_t size)
{
	t_mem_cookie	*mem;

	mem = (t_mem_cookie *)cookie;
	if (size > mem->size - (size_t)(mem->curr - (char *)mem->buff))
		size = mem->size - (size_t)(mem->curr - (char *)mem->buff);
	if (mem->curr && size > 0)
	{
		ft_memcpy(mem->curr, buff, size);
		mem->curr += size;
	}
	if (mem->size > (size_t)(mem->curr - (char *)mem->buff))
		*(mem->curr) = '\0';
	return (size);
}

static ssize_t			read_mem(void *cookie, char *buff, size_t size)
{
	t_mem_cookie	*mem;

	mem = (t_mem_cookie *)cookie;
	if (size > mem->size - (size_t)(mem->curr - (char *)mem->buff))
		size = mem->size - (size_t)(mem->curr - (char *)mem->buff);
	if (mem->curr && size > 0)
	{
		ft_memcpy(buff, mem->curr, size);
		mem->curr += size;
	}
	return (size);
}

static int				close_mem(void *cookie)
{
	t_mem_cookie	*mem;

	mem = (t_mem_cookie *)cookie;
	if (mem->allocated)
		ft_memdel((void **)&(mem->buff));
	ft_memdel((void **)&mem);
	return (0);
}

static t_stream_funs	g_mem_funs = {
	.write = &write_mem,
	.read = &read_mem,
	.close = &close_mem,
};

t_stream				*ft_fmemopen(void *buf, size_t size, const char *mode)
{
	t_mem_cookie	*cookie;

	if (!(cookie = (t_mem_cookie *)ft_memalloc(sizeof(*cookie))))
		return (NULL);
	if (!buf)
	{
		cookie->buff = NULL;
		if (size > 0 && !(cookie->buff = ft_memalloc(size)))
		{
			ft_memdel((void **)&cookie);
			return (NULL);
		}
		cookie->allocated = 1;
	}
	else
		cookie->buff = buf;
	cookie->curr = cookie->buff;
	cookie->size = size;
	return (ft_fopencookie(cookie, mode, g_mem_funs));
}
