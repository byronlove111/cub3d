/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:21:28 by abbouras          #+#    #+#             */
/*   Updated: 2025/12/02 11:59:15 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_player(t_image *img, t_game *game)
{
	int		i;
	int		j;
	int		size;
	int		start_x;
	int		start_y;

	size = 20;
	start_x = (int)(game->player.pos_x * 20) - size / 2;
	start_y = (int)(game->player.pos_y * 20) - size / 2;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(img, start_x + j, start_y + i, 0x00FF0000);
			j++;
		}
		i++;
	}
}

void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}