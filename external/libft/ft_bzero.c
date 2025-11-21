/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:29:02 by abbouras          #+#    #+#             */
/*   Updated: 2024/10/24 21:29:02 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = s;
	if (n == 0)
		return ;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}
/*
#include <stdio.h>
int	main(void)
{
	char str[50] = "Bonjour, je suis une chaîne de caractères!";
	printf("Avant ft_bzero: %s\n", str);

	ft_bzero(str, 20);

	printf("Après ft_bzero: ");
	for (int i = 0; i < 50; i++)
	{
		if (str[i] == '\0')
		{
			printf("\\0");
		} 
		else
		{
			printf("%c", str[i]);
		}
	}
	printf("\n");
}*/