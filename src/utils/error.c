/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:07:07 by abbouras          #+#    #+#             */
/*   Updated: 2025/12/01 11:19:09 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_error(char *error)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(error, 2);
	ft_putchar_fd('\n', 2);
	exit(1);
}