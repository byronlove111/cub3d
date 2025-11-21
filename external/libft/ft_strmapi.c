/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:53:07 by abbouras          #+#    #+#             */
/*   Updated: 2024/10/29 15:53:07 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new_s;

	if (!s)
		return (NULL);
	if (!f)
		return ((char *)s);
	i = 0;
	new_s = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!new_s)
		return (NULL);
	while (s[i])
	{
		new_s[i] = f(i, s[i]);
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}
/*
char	new_char(unsigned int i, char c)
{
	return 'a';
}

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
int	main(int ac, char **av)
{
	(void)ac;
	char *result = ft_strmapi((char* const)av[1], &new_char);
	printf("%s\n", result);
	free(result); 
}*/