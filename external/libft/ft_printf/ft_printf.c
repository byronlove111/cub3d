/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:20:39 by abbouras          #+#    #+#             */
/*   Updated: 2024/11/20 20:22:30 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	_putptr(unsigned long *ptr, int *ct)
{
	unsigned long	addr;

	addr = (unsigned long)ptr;
	if (addr == 0)
		*ct += write(1, "(nil)", 5);
	else
	{
		_putstr_fd("0x", 1, ct);
		_putnbr_base_ul(addr, "0123456789abcdef", ct);
	}
}

void	_putunsigned_fd(unsigned int n, int fd, int *ct)
{
	if (n > 9)
		_putunsigned_fd(n / 10, fd, ct);
	_putchar_fd((n % 10) + 48, fd, ct);
}

void	_putnbr_base(unsigned int nbr, char *base, int *ct)
{
	unsigned int	base_l;

	base_l = __strlen(base);
	if (nbr >= base_l)
	{
		_putnbr_base(nbr / base_l, base, ct);
	}
	_putchar_fd(base[nbr % base_l], 1, ct);
}

static void	if_statement(char c, va_list args, int *ct)
{
	if (c == 'c')
		_putchar_fd(va_arg(args, int), 1, ct);
	else if (c == 's')
		_putstr_fd(va_arg(args, char *), 1, ct);
	else if (c == 'i' || c == 'd')
		_putnbr_fd(va_arg(args, int), 1, ct);
	else if (c == 'x')
		_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef", ct);
	else if (c == 'X')
		_putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF", ct);
	else if (c == 'u')
		_putunsigned_fd(va_arg(args, unsigned int), 1, ct);
	else if (c == 'p')
		_putptr(va_arg(args, unsigned long *), ct);
	else if (c == '%')
		_putchar_fd('%', 1, ct);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		*ct;
	int		count;

	if (!str)
		return (-1);
	count = 0;
	ct = &count;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if_statement(*str++, args, ct);
		}
		else
		{
			write(1, str++, 1);
			(*ct)++;
		}
	}
	va_end(args);
	return (count);
}
