/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:17:40 by abbouras          #+#    #+#             */
/*   Updated: 2025/02/24 23:57:47 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			count++;
			while (*s != c && *s)
				s++;
		}
	}
	return (count);
}

void	free_split(char **strs, int i)
{
	while (i >= 0)
	{
		free(strs[i]);
		i--;
	}
	free(strs);
}

char	*alloc_word(char const *s, char c)
{
	int		i;
	char	*w;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	w = malloc(sizeof(char) * (i + 1));
	if (!w)
		return (NULL);
	i = 0;
	while (*s != c && *s)
		w[i++] = *s++;
	w[i] = '\0';
	return (w);
}

int	add_words_to_array(char **strs, char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			strs[i] = alloc_word(s, c);
			if (!strs[i])
			{
				free_split(strs, i - 1);
				return (0);
			}
			i++;
			while (*s != c && *s)
				s++;
		}
	}
	strs[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;

	if (!s)
		return (NULL);
	if (*s == '\0')
	{
		strs = malloc(sizeof(char *));
		if (!strs)
			return (NULL);
		strs[0] = NULL;
		return (strs);
	}
	strs = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!strs)
		return (NULL);
	if (!add_words_to_array(strs, s, c))
		return (NULL);
	return (strs);
}

/*
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
void	print_matrice(char **strs)
{
	int i = 0;
	int j;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			write(1, &strs[i][j], 1);
			j++;
		}
		if (strs[i][j] == '\0')
			write(1, "/0", 2);
		write(1, "\n", 1);
		i++;
	}
	if (strs[i] == NULL)
		write(1, "NULL\n", 5);
}

void	free_matrice(char **strs)
{
	int i = 0;

	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}


int	main(int ac, char **av)
{
	(void)ac;
	char **strs = ft_split(av[1], av[2][0]);
	if (!strs)
		return (1);
	print_matrice(strs);
	free_matrice(strs);
}*/
