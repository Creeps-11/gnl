/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wskrzyni <wskrzyni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:49:56 by wskrzyni          #+#    #+#             */
/*   Updated: 2025/01/10 10:39:48 by wskrzyni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	char	*ptr;

	ptr = s;
	while (n--)
	{
		*ptr = '\0';
		ptr++;
	}
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	while (src[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	destsize;
	unsigned int	srcsize;

	i = 0;
	destsize = ft_strlen(dest);
	srcsize = ft_strlen(src);
	if (size == 0 || destsize > size)
		return (size + srcsize);
	if (!src[0])
		return (destsize);
	while (src[i] != '\0' && (destsize + i) < size - 1)
	{
		dest[destsize + i] = src[i];
		i++;
	}
	dest[destsize + i] = '\0';
	return (destsize + srcsize);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*sjoin;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	sjoin = (char *)malloc((sizeof(char) * (s1len + s2len) + 1));
	if (!sjoin)
		return (NULL);
	ft_strlcpy(sjoin, s1, s1len + 1);
	ft_strlcat(sjoin, s2, s1len + s2len + 1);
	return (free(s1), sjoin);
}
