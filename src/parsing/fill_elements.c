/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:00:31 by mehdi             #+#    #+#             */
/*   Updated: 2025/12/02 11:54:11 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	*dup_no_nl(char *s)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != '\n')
		len++;
	return (ft_substr(s, 0, len));
}

static void	assign_value(char **dest, char *str, int *x, int skip)
{
	*x += skip;
	while (str[*x] == ' ')
		(*x)++;
	*dest = dup_no_nl(&str[*x]);
}

static int	parse_color_element(t_game *g, char *str, int *x, char type)
{
	char	*temp_color;
	int		color;

	*x += 1;
	while (str[*x] == ' ')
		(*x)++;
	temp_color = dup_no_nl(&str[*x]);
	color = parse_color(temp_color);
	free(temp_color);
	if (color == -1)
		return (0);
	if (type == 'F')
		g->floor_color = color;
	else
		g->ceiling_color = color;
	return (1);
}

static int	parse_element(t_game *g, char *str, int *x, int *count)
{
	if (!strncmp(&str[*x], "NO", 2))
		return (assign_value(&g->textures.north, str, x, 2), (*count)++, 1);
	if (!strncmp(&str[*x], "SO", 2))
		return (assign_value(&g->textures.south, str, x, 2), (*count)++, 1);
	if (!strncmp(&str[*x], "WE", 2))
		return (assign_value(&g->textures.west, str, x, 2), (*count)++, 1);
	if (!strncmp(&str[*x], "EA", 2))
		return (assign_value(&g->textures.east, str, x, 2), (*count)++, 1);
	if (str[*x] == 'F')
		return (parse_color_element(g, str, x, 'F'), (*count)++, 1);
	if (str[*x] == 'C')
		return (parse_color_element(g, str, x, 'C'), (*count)++, 1);
	return (0);
}

int	fill_elements(t_game *g, int *count_element, int *row_map_y)
{
	int	y;
	int	x;

	y = 0;
	*count_element = 0;
	*row_map_y = -1;
	while (g->map.data[y])
	{
		x = 0;
		while (g->map.data[y][x] == ' ')
			x++;
		if (!g->map.data[y][x] || g->map.data[y][x] == '\n')
		{
			y++;
			continue ;
		}
		if (parse_element(g, g->map.data[y], &x, count_element))
			;
		else if (g->map.data[y][x] == '1')
			return (*row_map_y = y, 1);
		else
			return (0);
		y++;
	}
	return (1);
}