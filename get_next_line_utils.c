/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raugo <raugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:29:09 by raugo             #+#    #+#             */
/*   Updated: 2021/11/20 20:26:51 by raugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char			*dest;
	unsigned const char		*source;
	size_t					a;

	dest = dst;
	source = src;
	a = 0;
	if (dest < source)
	{
		while (a < n)
		{
			dest[a] = source[a];
			a++;
		}
	}
	else
	{
		while (n > 0)
		{
			dest[n - 1] = source[n - 1];
			n--;
		}
	}
	return (dst);
}

size_t	ft_strlen(char *str)
{
	int	a;

	if (!str)
		return (0);
	a = 0;
	while (str[a] != 0)
		a++;
	return (a);
}

char	*ft_strchr(const char *s, int c)
{
	int		a;
	char	*str;

	if (!s)
		return (0);
	str = (char *)s;
	a = 0;
	while (s[a] != 0)
	{
		if (s[a] == c)
			return (str + a);
		a++;
	}
	if (s[a] == c)
		return (str + a);
	return (0);
}
