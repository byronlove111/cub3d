/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_char_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:35:01 by mehdi             #+#    #+#             */
/*   Updated: 2025/12/01 11:49:22 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_left_wall(char **map)
{
	int	y;

	y = 0;
	while (map[y])
	{
		if (map[y][0] != '1' && map[y][0] != ' ')
			return (0);
		y++;
	}
	return (1);
}

static int	is_invalid_map_char(char c)
{
	return (!(c == ' ' || c == '1' || c == '0' || c == 'N'
			|| c == 'S' || c == 'E' || c == 'W' || c == '\n'));
}

int	check_char(char **map)
{
	int	x;
	int	y;
	int	count;

	x = 0;
	y = 0;
	count = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (is_invalid_map_char(map[y][x]))
				return (0);
			if (map[y][x] == 'N' || map[y][x] == 'S' ||
				map[y][x] == 'E' || map[y][x] == 'W')
				count++;
			x++;
		}
		x = 0;
		y++;
	}
	if (count == 1)
		return (1);
	else
		return (0);
}

int	check_top_bottom_walls(char **map)
{
	int	x;
	int	height;

	height = 0;
	while (map[height])
		height++;
	x = 0;
	while (map[0][x])
	{
		if (map[0][x] != '1' && map[0][x] != ' ' && map[0][x] != '\n')
			return (0);
		x++;
	}
	x = 0;
	while (map[height - 1][x])
	{
		if (map[height - 1][x] != '1' && map[height - 1][x] != ' '
			&& map[height - 1][x] != '\n')
			return (0);
		x++;
	}
	return (1);
}