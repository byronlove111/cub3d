/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:35:11 by abbouras          #+#    #+#             */
/*   Updated: 2024/10/25 21:35:11 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*tmp;
	size_t			i;

	i = 0;
	tmp = (unsigned char *)s;
	if (n == 0)
		return (s);
	while (i < n)
	{
		tmp[i] = c;
		i++;
	}
	return (s);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("Usage: %s <char> <num>\n", argv[0]);
		return (1);
	}

	size_t n = (size_t)atoi(argv[2]);
	char *str = (char *)malloc(n + 1);
	if (!str)
		return (1);
	
	str[n] = '\0';
	ft_memset(str, argv[1][0], n);
	printf("Result of ft_memset: %s\n", str);
	memset(str, argv[1][0], n);
	printf("Result of memset: %s\n", str);
	free(str);
}*/