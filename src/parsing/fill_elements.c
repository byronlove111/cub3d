/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:00:31 by mehdi             #+#    #+#             */
/*   Updated: 2025/12/02 10:16:20 by abbouras         ###   ########.fr       */
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
	g->count_element++;
	return (1);
}

static int	parse_element(t_game *g, char *str, int *x)
{
	if (!strncmp(&str[*x], "NO", 2))
		return (assign_value(&g->north_wall, str, x, 2), g->count_element++, 1);
	if (!strncmp(&str[*x], "SO", 2))
		return (assign_value(&g->south_wall, str, x, 2), g->count_element++, 1);
	if (!strncmp(&str[*x], "WE", 2))
		return (assign_value(&g->west_wall, str, x, 2), g->count_element++, 1);
	if (!strncmp(&str[*x], "EA", 2))
		return (assign_value(&g->east_wall, str, x, 2), g->count_element++, 1);
	if (str[*x] == 'F')
		return (parse_color_element(g, str, x, 'F'));
	if (str[*x] == 'C')
		return (parse_color_element(g, str, x, 'C'));
	return (0);
}

int	fill_elements(t_game *g)
{
	int	y;
	int	x;

	y = 0;
	while (g->map[y])
	{
		x = 0;
		while (g->map[y][x] == ' ')
			x++;
		if (!g->map[y][x] || g->map[y][x] == '\n')
		{
			y++;
			continue ;
		}
		if (parse_element(g, g->map[y], &x))
			;
		else if (g->map[y][x] == '1')
			return (g->row_map_y = y, 1);
		else
			return (0);
		y++;
	}
	return (1);
}