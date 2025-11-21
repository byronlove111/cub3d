/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:55:19 by abbouras          #+#    #+#             */
/*   Updated: 2024/12/10 03:36:11 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	__strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*_strjoin(char const *s1, char const *s2)
{
	size_t			size;
	size_t			i;
	char			*str;

	if (!s1 || !s2)
		return (NULL);
	size = __strlen(s1) + __strlen(s2);
	i = 0;
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	while (*s1)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}

char	*_strchr(const char *s, int c)
{
	unsigned char	u_c;

	u_c = (unsigned char)c;
	while (*s)
	{
		if (*s == u_c)
			return ((char *)s);
		s++;
	}
	if (u_c == '\0')
		return ((char *)s);
	return (NULL);
}

void	*_calloc(size_t elementCount, size_t elementSize)
{
	unsigned char	*ptr;
	size_t			i;

	if (elementSize * elementCount > SIZE_MAX)
		return (NULL);
	ptr = malloc(elementSize * elementCount);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < (elementCount * elementSize))
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}
