/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:47:26 by abbouras          #+#    #+#             */
/*   Updated: 2024/10/29 17:47:26 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		n = -n;
		ft_putchar_fd('-', fd);
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd((n % 10) + 48, fd);
}

/*#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
int	main(int ac, char **av)
{
	(void)ac;
	ft_putnbr_fd(atoi(av[1]), atoi(av[2]));
}*/