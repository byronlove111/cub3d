/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:37:07 by abbouras          #+#    #+#             */
/*   Updated: 2024/10/24 22:37:07 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmp;
	size_t			i;
	unsigned char	u_c;

	tmp = (unsigned char *)s;
	u_c = (unsigned char)c;
	i = 0;
	if (n <= 0)
		return (NULL);
	while (i < n)
	{
		if (tmp[i] == u_c)
			return (&tmp[i]);
		i++;
	}
	return (NULL);
}

/*#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
int	main(int ac, char **av)
{
	if (ac != 4)
	{
		printf("Usage: %s <string> <char> <num>\n", av[0]);
		return (1);
	}

	const char *str = av[1];
	int c = av[2][0];
	size_t n = (size_t)atoi(av[3]);

	void *result = ft_memchr(str, c, n);
	void *result2= ft_memchr(str, c, n);
	if (result)
		printf("Character found: %c\n", *(unsigned char *)result);
	else
		printf("Character not found within the first %zu bytes.\n", n);
	if (result2)
		printf("Character found: %c\n", *(unsigned char *)result);
	else
		printf("Character not found within the first %zu bytes.\n", n);
}*/