/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ioutils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acyrenna <acyrenna@school21.ru>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 19:01:18 by acyrenna          #+#    #+#             */
/*   Updated: 2021/01/10 19:01:57 by acyrenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		sfopen(char *path, int flags)
{
	int	fd;

	if ((fd = open(path, flags)) < 1)
		gexit(ERROR_INVALID_FILE, path, "", "");
	return (fd);
}

void	*sfread(int fd, void *buf, size_t nbytes, char *path)
{
	char	*cbuf;

	cbuf = (char *)buf;
	if ((int)(read(fd, buf, nbytes)) != (int)nbytes)
		gexit(ERROR_INVALID_FILE_READ, path, ft_itoa(nbytes), "");
	cbuf[nbytes] = 0;
	return (buf);
}
