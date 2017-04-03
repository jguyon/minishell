/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_streams.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 03:17:31 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/14 12:04:46 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STREAMS_H
# define FT_STREAMS_H

/*
** Buffered stream implementation
*/

# include <stdlib.h>
# include <unistd.h>

/*
** FT_BUFSIZ - default size of buffers
*/
# define FT_BUFSIZ 1024

/*
** FT_IONBF, FT_IOFBF - flags for configuring stream buffering
*/
# define FT_IONBF 0x1
# define FT_IOFBF 0x2

/*
** FT_EOF - end of file or error indicator
*/
# define FT_EOF -1

/*
** FT_FOPEN_MAX - max number of stream that can be open at the same time
*/
# define FT_FOPEN_MAX 16

/*
** t_stream_read, t_stream_write, t_stream_close - custom stream functions
*/
typedef ssize_t	t_stream_write(void *cookie, const char *buff, size_t size);
typedef ssize_t	t_stream_read(void *cookie, char *buff, size_t size);
typedef int		t_stream_close(void *cookie);

/*
** t_stream_funs - type for holding custom stream functions
*/
typedef struct	s_stream_funs {
	t_stream_write	*write;
	t_stream_read	*read;
	t_stream_close	*close;
}				t_stream_funs;

/*
** Private flags used in stream structure
*/
# define FT_IOWR	0x4
# define FT_IORD	0x8
# define FT_IOERR	0x10
# define FT_IOEOF	0x20
# define FT_IOUSRBF 0x40

/*
** t_stream - stream type
**
** Members of this struct should not be accessed outside of this library.
*/
typedef struct	s_stream {
	int				flags;
	int				fd;
	void			*cookie;
	t_stream_write	*write;
	t_stream_read	*read;
	t_stream_close	*close;
	size_t			size;
	char			*curr;
	char			*eof;
	char			*buff;
}				t_stream;

/*
** FT_STDIN, FT_STDOUT, FT_STDERR - standard streams
**
** Since these macros are just aliases to global variables, directly
** reassigning them (after having closed them) to other streams is possible.
** This could especially be useful for testing command line programs.
*/
t_stream		*g_ft_stdin;
t_stream		*g_ft_stdout;
t_stream		*g_ft_stderr;
# define FT_STDIN	g_ft_stdin
# define FT_STDOUT	g_ft_stdout
# define FT_STDERR	g_ft_stderr

/*
** ft_fopencookie - open a custom stream
** @cookie: cookie to pass to functions in @funs
** @mode: opening mode
** @funs: functions called when writing to or closing the stream
**
** Returns null if an error occured.
*/
t_stream		*ft_fopencookie(void *cookie, const char *mode,
								t_stream_funs funs);

/*
** ft_memopen - open a stream to write in a given string
** @buf: buffer to write to
** @size: size of the buffer
** @mode: opening mode
**
** Will append a '\0' when flushing or closing if possible,
** @size should account for it.
*/
t_stream		*ft_fmemopen(void *buf, size_t size, const char *mode);

/*
** ft_open_memstream - open a stream to write in dynamically allocated string
** @ptr: pointer to store the string
** @sizeloc: point to store the size of the string
**
** The initial values that @ptr and @sizeloc point to will be ignored.
** The string pointed to by @ptr will be allocated and grown as needed,
** storing its size in the value pointed by @sizeloc.
*/
t_stream		*ft_open_memstream(char **ptr, size_t *sizeloc);

/*
** ft_fdopen - open a stream using an open file descriptor
** @fd: file descriptor
** @mode: opening mode
**
** Note that @fd will be closed when the stream is closed.
*/
t_stream		*ft_fdopen(int fd, const char *mode);

/*
** ft_setvbuf - change the buffer associated with the stream
** @stm: the stream
** @buff: buffer to assign to @stm
** @mode: FT_IOFBF for full buffering, FT_IONBF for no buffering
** @size: size of the buffer
**
** If @buff is null, it will be allocated in the next io operation.
** Returns 0 if successful, FT_EOF otherwise.
*/
int				ft_setvbuf(t_stream *stm, char *buff, int mode, size_t size);

/*
** ft_fwrite - write to a stream
** @mem: buffer to write from
** @size: size of an item of data in bytes
** @n: number of items of data to write
** @stm: stream to write to
**
** Returns the number of items of data sucessfully written.
*/
size_t			ft_fwrite(const void *mem, size_t size, size_t n,
					t_stream *stm);

/*
** ft_fread - read from a stream
** @mem: buffer to read to
** @size: size of an item of data in bytes
** @n: number of items of data to read
** @stm: stream to read from
**
** Returns the number of items of data successfully read.
*/
size_t			ft_fread(void *mem, size_t size, size_t n, t_stream *stm);

/*
** ft_fputc - write a character
** @c: character to write
** @stm: stream to write to
*/
int				ft_fputc(int c, t_stream *stm);

/*
** ft_fgetc - read a character from a stream
** @stm: stream to read from
*/
int				ft_fgetc(t_stream *stm);

/*
** ft_fputs - write a string
** @s: null-terminated string to write
** @stm: stream to write to
**
** Returns 0 if successful, FT_EOF otherwise.
*/
int				ft_fputs(const char *s, t_stream *stm);

/*
** ft_fgets - read into a string
** @s: buffer to read into
** @size: size of the buffer, including the '\0'
** @stm: stream to read from
**
** Reading stops when @size has been reached, on eof, or after a newline.
** Returns null on error or when eof occurs before reading any character,
** @s otherwise.
*/
char			*ft_fgets(char *s, int size, t_stream *stm);

/*
** ft_ferror - check if a stream has failed
** @stm: stream to check
*/
int				ft_ferror(t_stream *stm);

/*
** ft_feof - check if a stream is at eof
** @stm: stream to check
*/
int				ft_feof(t_stream *stm);

/*
** ft_clearerr - clear the error indicator
** @stm: stream to clear
*/
void			ft_clearerr(t_stream *stm);

/*
** ft_fflush - flush the buffer associated with a stream
** @stm: stream to flush
**
** Returns 0 if successful, FT_EOF otherwise.
** If @stm is null, all open streams are flushed.
*/
int				ft_fflush(t_stream *stm);

/*
** ft_fclose - flush and close a stream
** @stm: stream to close
**
** Returns 0 if successful, FT_EOF otherwise.
*/
int				ft_fclose(t_stream *stm);

/*
** ft_fcloseall - close all open streams
**
** Returns 0 if successful, FT_EOF otherwise.
*/
int				ft_fcloseall(void);

/*
** Private global used to store all streams
*/
t_stream		g_ft_streams[FT_FOPEN_MAX];

/*
** Private type used by ft_fmemopen to store the cookie
*/
typedef struct	s_mem_cookie {
	int			allocated;
	size_t		size;
	void		*buff;
	char		*curr;
}				t_mem_cookie;

/*
** Private type used by ft_open_memstream to store the cookie
*/
typedef struct	s_ptr_cookie {
	size_t		*sizeloc;
	char		**ptr;
	size_t		fullsize;
}				t_ptr_cookie;

#endif
