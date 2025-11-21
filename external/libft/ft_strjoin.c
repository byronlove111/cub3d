/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:43:12 by abbouras          #+#    #+#             */
/*   Updated: 2024/10/27 12:43:12 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			size;
	size_t			i;
	char			*str;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	while (*s1)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}

/*#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
int	main(int ac, char **av)
{
	(void)ac;
	char 	*str = ft_strjoin(av[1], av[2]);
	if (!str)
		return (1);
	printf("%s\n", str);
	free(str);
}*/
