/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:37:25 by mehdi             #+#    #+#             */
/*   Updated: 2025/12/01 11:53:08 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	fill_square_map(t_game *game, char **map)
{
	int		x;
	int		y;
	int		height;
	size_t	max_line;

	max_line = ft_strlen(map[0]);
	y = 0;
	height = 0;
	while (map[height])
		height++;
	while (map[y])
	{
		if (ft_strlen(map[y]) > max_line)
			max_line = ft_strlen(map[y]);
		y++;
	}
	game->square_map = malloc(sizeof(char *) * (height + 1));
	if (!game->square_map)
		return ;
	y = 0;
	while (y < height)
	{
		x = 0;
		game->square_map[y] = malloc(sizeof(char) * (max_line + 1));
		if (!game->square_map[y])
			return ;
		while (map[y][x])
		{
			if (map[y][x] == ' ' || map[y][x] == '\n')
				game->square_map[y][x] = '2';
			else
				game->square_map[y][x] = map[y][x];
			x++;
		}
		while (x < (int)max_line)
		{
			game->square_map[y][x] = '2';
			x++;
		}
		game->square_map[y][x] = '\0';
		y++;
	}
	game->square_map[y] = NULL;
}

int	map_close(char **map)
{
	int	x;
	int	y;
	int	len;

	print_map(map);
	x = 1;
	y = 1;
	len = 0;
	while (map[len])
		len++;
	while (y < len - 1)
	{
		while (map[y][x])
		{
			if (map[y][x] == '0' || map[y][x] == 'N' ||
				map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W')
			{
				if (map[y+1][x] == '2' || map[y-1][x] == '2'
					|| map[y][x+1] == '2' || map[y][x-1] == '2')
					return (0);
			}
			x++;
		}
		x = 1;
		y++;
	}
	return (1);
}