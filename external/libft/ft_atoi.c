/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:06:19 by abbouras          #+#    #+#             */
/*   Updated: 2024/10/24 13:06:19 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	number;
	int	sign;

	i = 0;
	number = 0;
	sign = 0;
	while (ft_isspace(str[i]) && str[i])
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' )
	{
		number = (number * 10) + str[i] - 48;
		i++;
	}
	if (sign == 1)
		number = -number;
	return (number);
}
/*#include <stdio.h>
#include <stdlib.h>
int	main(int ac, char **av)
{
	printf("atoi %d\n", atoi(av[1]));		
	printf("mine %d\n", ft_atoi(av[1]));
}*/