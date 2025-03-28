/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wskrzyni <wskrzyni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:49:36 by wskrzyni          #+#    #+#             */
/*   Updated: 2025/01/10 13:03:44 by wskrzyni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	c = (unsigned char)c;
	while (s[i] != '\0' && s[i] != c)
		i++;
	if (s[i] == c)
		return (i);
	return (-1);
}

static void	store_split(char *buffer, char store[BUFFER_SIZE + 1])
{
	int	index;

	index = ft_strchr(buffer, '\n') + 1;
	if (index == 0)
		index = ft_strlen(buffer);
	ft_strlcpy(buffer, buffer, index + 1);
	index = ft_strchr(store, '\n') + 1;
	ft_strlcpy(store, store + index, (BUFFER_SIZE + 1) - index);
}

static char	*add_to_buffer(char *buffer, char store[BUFFER_SIZE + 1], int fd)
{
	int	count_bytes;

	if (store && store[0] != '\0')
	{
		buffer = ft_strjoin(buffer, store);
		if (!buffer)
			return (free(buffer), NULL);
	}
	count_bytes = 1;
	while (ft_strchr(buffer, '\n') < 0 && count_bytes > 0)
	{
		count_bytes = read(fd, store, BUFFER_SIZE);
		if ((count_bytes == 0 && store[0] == '\0') || count_bytes == -1)
			return (free(buffer), NULL);
		store[count_bytes] = '\0';
		buffer = ft_strjoin(buffer, store);
		if (!buffer)
			return (free(buffer), NULL);
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	store [BUFFER_SIZE + 1] = {0};

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = (char *) malloc((sizeof(char) * BUFFER_SIZE) + 1);
	if (!buffer)
		return (NULL);
	ft_bzero((void *)buffer, BUFFER_SIZE + 1);
	buffer = add_to_buffer(buffer, store, fd);
	if (!buffer)
		return (ft_bzero((void *)store, BUFFER_SIZE + 1), NULL);
	store_split(buffer, store);
	return (buffer);
}
