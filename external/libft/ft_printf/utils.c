/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:29:56 by abbouras          #+#    #+#             */
/*   Updated: 2024/11/14 17:41:43 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	_putchar_fd(char c, int fd, int *ct)
{
	write(fd, &c, 1);
	(*ct)++;
}

void	_putstr_fd(char *s, int fd, int *ct)
{
	if (!s)
	{
		*ct += write(1, "(null)", 6);
		return ;
	}
	while (*s)
	{
		_putchar_fd(*s, fd, ct);
		s++;
	}
}

void	_putnbr_fd(int n, int fd, int *ct)
{
	if (n == -2147483648)
	{
		_putstr_fd("-2147483648", fd, ct);
		return ;
	}
	if (n < 0)
	{
		n = -n;
		_putchar_fd('-', fd, ct);
	}
	if (n > 9)
		_putnbr_fd(n / 10, fd, ct);
	_putchar_fd((n % 10) + 48, fd, ct);
}

void	_putnbr_base_ul(unsigned long nbr, char *base, int *ct)
{
	unsigned long	base_l;

	base_l = _strlen(base);
	if (nbr >= base_l)
		_putnbr_base_ul(nbr / base_l, base, ct);
	_putchar_fd(base[nbr % base_l], 1, ct);
}
