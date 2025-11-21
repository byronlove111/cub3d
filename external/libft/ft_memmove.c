/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:04:55 by abbouras          #+#    #+#             */
/*   Updated: 2024/10/26 16:04:55 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const	void *src, size_t len)
{
	unsigned char	*p_dst;
	unsigned char	*p_src;

	if (!dst && !src)
		return (NULL);
	p_dst = (unsigned char *)dst;
	p_src = (unsigned char *)src;
	if (src < dst)
		while (len--)
			p_dst[len] = p_src[len];
	else
		while (len--)
			*p_dst++ = *p_src++;
	return (dst);
}

/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char src[] = "Ceci est un test de memmove";
	char dst[50] = {0};

	printf("Avant ft_memmove, dst: \"%s\"\n", dst);
	ft_memmove(dst, src, strlen(src) + 1);
	printf("Après ft_memmove, dst: \"%s\"\n", dst);

	printf("\nComparaison avec ft_memcpy\n\n");
	char overlap[] = "1234567890";
	printf("ft_memmove : Avant chevauchement, overlap: \"%s\"\n", overlap);
	ft_memmove(overlap + 4, overlap, 6);
	printf("ft_memmove : Après chevauchement, overlap: \"%s\"\n", overlap);

	char overlap2[] = "1234567890";
	printf("ft_memcpy : Avant chevauchement, overlap: \"%s\"\n", overlap2);
	ft_memcpy(overlap2 + 4, overlap2, 6);
	printf("ft_memcpy : Après chevauchement, overlap: \"%s\"\n", overlap2);
	return 0;
}
*/