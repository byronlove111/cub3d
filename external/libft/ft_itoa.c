/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:13:00 by abbouras          #+#    #+#             */
/*   Updated: 2024/10/27 17:13:00 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	find_size(long nb)
{
	long	size;

	size = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		size++;
		nb = -nb;
	}
	while (nb > 0)
	{
		nb /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	long	nb;
	long	i;
	char	*str;

	nb = n;
	i = find_size(nb) - 1;
	str = malloc(sizeof(char) * find_size(nb) + 1);
	if (!str)
		return (NULL);
	str[i + 1] = '\0';
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		str[i] = nb % 10 + 48;
		nb /= 10;
		i--;
	}
	return (str);
}
/*
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
int	main(int ac, char **av)
{
	(void)ac;
	char *str = ft_itoa(atoi(av[1]));
	printf("%s\n", str);
	free(str);
}*/