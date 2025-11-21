/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:01:18 by abbouras          #+#    #+#             */
/*   Updated: 2024/10/24 16:01:18 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		size;
	int		i;
	char	*str;

	i = 0;
	size = ft_strlen(s);
	str = malloc(size + 1);
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
int	main(int ac, char **av)
{
	(void)ac;
	const char *original = av[1]; 
	char *copy = ft_strdup(original);
	
	int i = 0;
	for (; copy[i] != '\0'; i++)
	{
		write(1, &copy[i], 1);
	}
	if (copy[i] == '\0')
		write(1, "/0", 2);

	free(copy); 
}*/