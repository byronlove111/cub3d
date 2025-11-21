/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:50:20 by abbouras          #+#    #+#             */
/*   Updated: 2024/10/25 19:50:20 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*tmp;
	unsigned char	*tmp2;
	size_t			i;	

	i = 0;
	tmp = (unsigned char *) s1;
	tmp2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (tmp[i] != tmp2[i])
			return (tmp[i] - tmp2[i]);
		i++;
	}
	return (0);
}
/*
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
int	main(int ac, char **av)
{
	(void)ac;
	void	*s1 = av[1];
	void	*s2 = NULL;
	size_t n = atoi(av[3]);
	printf("%d\n", ft_memcmp(s1, s2, n));
	printf("%d\n", memcmp(s1, s2, n));
}*/