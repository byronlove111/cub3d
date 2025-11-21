/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:29:39 by abbouras          #+#    #+#             */
/*   Updated: 2024/10/26 15:29:39 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char		*last;
	unsigned char	u_c;

	u_c = (unsigned char)c;
	last = NULL;
	while (*s)
	{
		if (*s == u_c)
			last = s;
		s++;
	}
	if (u_c == '\0')
		return ((char *)s);
	return ((char *)last);
}

/*#include <string.h>
#include <stdio.h>
int	main(void)
{
	const char *path = "home/user/documents/example.txt";
	const char *filename = strrchr(path, '/');
	if (filename)
		printf("Le nom du fichier est : %s\n", filename);
	else
		printf("Non trouve\n");
}*/