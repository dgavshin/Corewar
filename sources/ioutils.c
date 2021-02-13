/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ioutils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <acyrenna@school21.ru>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 19:01:18 by acyrenna          #+#    #+#             */
/*   Updated: 2021/02/13 15:31:47 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		sfopen(char *path, int flags)
{
	int	fd;

	if ((fd = open(path, flags)) < 1)
		gexit(g_error_invalid_file, path, "", "");
	return (fd);
}

void	*sfread(int fd, void *buf, size_t nbytes, char *path)
{
	char	*cbuf;

	cbuf = (char *)buf;
	if ((int)(read(fd, buf, nbytes)) != (int)nbytes)
		gexit(g_error_invalid_file_read, path, ft_itoa(nbytes), "");
	cbuf[nbytes] = 0;
	return (buf);
}

off_t	get_file_size(const char *filename)
{
	off_t	v1;
	int		fd;

	fd = open(filename, 0);
	if (fd < 0)
	{
		ft_printf("Can't read source file %s\n", filename);
		exit(1);
	}
	v1 = lseek(fd, 0LL, 2);
	close(fd);
	return (v1);
}
