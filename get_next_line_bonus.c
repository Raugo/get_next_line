/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raugo <raugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:42:39 by raugo             #+#    #+#             */
/*   Updated: 2021/11/20 20:23:07 by raugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "get_next_line.h"

char	*resizesbuffer(char *buffer, int ind)
{
	char	*tempbuffer;

	tempbuffer = malloc(ind + BUFFER_SIZE + 1);
	if (tempbuffer == 0)
		return (0);
	ft_memmove(tempbuffer, buffer, ind);
	free(buffer);
	return (tempbuffer);
}

char	*checkbuffer(int ind, int totalbytesreaded, char *buffer, char **save)
{
	if (ind < totalbytesreaded - 1 && buffer[ind] == '\n')
	{
		*save = malloc(totalbytesreaded - ind);
		buffer[totalbytesreaded] = 0;
		ft_memmove(*save, &buffer[ind + 1], totalbytesreaded - ind);
	}
	else if (ind == totalbytesreaded)
	{
		buffer[ind] = 0;
		return (buffer);
	}
	buffer[ind + 1] = 0;
	return (buffer);
}

char	*readbuffer(int fd, char *buffer, char **save, int bytesreaded)
{
	int	ind;
	int	totalbytesreaded;

	ind = 0;
	totalbytesreaded = bytesreaded;
	while (ind < totalbytesreaded && buffer[ind] != '\n' && buffer[ind] > 0)
	{
		ind++;
		if (ind == totalbytesreaded)
		{
			buffer = resizesbuffer(buffer, ind);
			bytesreaded = read(fd, buffer + ind, BUFFER_SIZE);
			totalbytesreaded += bytesreaded;
			if (bytesreaded == 0)
			{
				buffer[ind] = 0;
				return (buffer);
			}
		}
	}
	return (checkbuffer(ind, totalbytesreaded, buffer, save));
}

char	*checksave(char **save, int fd)
{
	char	*buffer;
	int		bytesreaded;

	bytesreaded = ft_strlen(*save);
	if (bytesreaded > 0)
	{
		buffer = *save;
		*save = 0;
	}
	else
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (buffer == 0)
			return (0);
		bytesreaded = read(fd, buffer, BUFFER_SIZE);
		if (bytesreaded <= 0)
		{
			free (buffer);
			return (0);
		}
	}
	buffer = readbuffer(fd, buffer, save, bytesreaded);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*save[4096];

	if (fd < 0 || fd > 4095 || BUFFER_SIZE <= 0)
		return (0);
	return (checksave(&save[fd], fd));
}
