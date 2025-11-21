/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:15:49 by abbouras          #+#    #+#             */
/*   Updated: 2024/10/27 14:15:49 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_charset(char c, char const *str)
{
	while (*str)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}

static int	find_size(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(s1) - 1;
	while (is_in_charset(s1[i], set) && s1[i])
		i++;
	if (!is_in_charset(s1[i], set) && s1[i])
		i--;
	while (is_in_charset(s1[j], set) && j >= 0)
		j--;
	return (j - i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		size;
	char	*str;

	if (!set || !s1)
		return (NULL);
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	i = 0;
	j = 0;
	size = find_size(s1, set);
	if (size <= 0)
		return (ft_strdup(""));
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	while (is_in_charset(s1[i], set) && s1[i])
		i++;
	while (j < size)
		str[j++] = s1[i++];
	return (str);
}

/*#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
void	print_word(char *str)
{
	while (*str)
	{
		write(1, &*str, 1);
		*str++;
	}
	if (*str == '\0')
		write(1, "/0", 2);
}

int	main(int ac, char **av)
{
	(void)ac;
	char *str = ft_strtrim(av[1], av[2]);
	print_word(str);
	free(str);
}*/