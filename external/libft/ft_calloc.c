/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:58:45 by abbouras          #+#    #+#             */
/*   Updated: 2024/10/24 16:58:45 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	unsigned char	*ptr;
	size_t			i;

	if (elementSize * elementCount > SIZE_MAX)
		return (NULL);
	ptr = malloc(elementSize * elementCount);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < (elementCount * elementSize))
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

/*#include <stdio.h>
int	main(void)
{
	int	num_elements = 5; 
	int	*array = (int *)ft_calloc(num_elements, sizeof(int));
	if (!array)
	{
		return (1); 
	}

	for (int i = 0; i < num_elements; i++)
	{
		array[i] = i * 2; 
	}

	for (int i = 0; i < num_elements; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");

	free(array);
}*/