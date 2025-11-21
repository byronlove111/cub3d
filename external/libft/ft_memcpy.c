/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:22:16 by abbouras          #+#    #+#             */
/*   Updated: 2024/10/25 21:22:16 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dst_tmp;
	unsigned char	*src_tmp;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	src_tmp = (unsigned char *)src;
	dst_tmp = (unsigned char *)dest;
	while (i < n)
	{
		dst_tmp[i] = src_tmp[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int	main(int ac, char **av)
{
	if (ac != 3)
	{
		printf("Usage: %s <source> <num>\n", av[0]);
		return (1);
	}

	size_t n = (size_t)atoi(av[2]);
	char *dest = (char *)malloc(n + 1);
	if (!dest)
		return (1);
	memset(dest, 0, n + 1);
	ft_memcpy(dest, av[1], n);
	printf("Result of ft_memcpy: %s\n", dest);
	memcpy(dest, av[1], n);
	printf("Result of memcpy: %s\n", dest);
	free(dest);
}*/