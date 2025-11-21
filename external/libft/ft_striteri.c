/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:21:23 by abbouras          #+#    #+#             */
/*   Updated: 2024/10/29 16:21:23 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void	test(unsigned int i, char *c)
{
	*c = 'a';
}

int	main(int ac, char **av)
{
	ft_striteri(av[1], &test);
	printf("Modified string: %s\n", av[1]);
}
*/
