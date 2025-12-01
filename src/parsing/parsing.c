/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:06:33 by mehdi             #+#    #+#             */
/*   Updated: 2025/12/01 11:50:21 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_struct(t_game *game)
{
	game->map = NULL;
	game->square_map = NULL;
	game->ceiling = NULL;
	game->east_wall = NULL;
	game->floor = NULL;
	game->north_wall = NULL;
	game->south_wall = NULL;
	game->west_wall = NULL;
	game->row_map_y = -1;
	game->count_element = 0;
}

int	check_file_cub(const char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4)
		return (0);
	return (ft_strncmp(file + len - 4, ".cub", 4) == 0);
}

void	print_map(char **map)
{
	int y;

	y = 0;
	while (map[y])
	{
		printf("%s", map[y]);
		printf("\n");
		y++;
	}
}

static int	check_elements_valid(t_game *g)
{
	if (g->count_element != 6)
		return (0);
	if (!g->north_wall || !g->south_wall || !g->west_wall
		|| !g->east_wall || !g->floor || !g->ceiling)
		return (0);
	if (g->row_map_y == -1)
		return (0);
	return (1);
}

int	parsing(t_game *game, char **av)
{
	init_struct(game);
	if (!check_file_cub(av[1]))
		ft_error("file is not a .cub");
	game->map = create_map(av[1]);
	if (!game->map)
		ft_error("void map");
	if (!fill_elements(game))
		ft_error("Invalid map");
	if (!check_elements_valid(game))
		ft_error("Invalid map");
	if (!check_left_wall(&game->map[game->row_map_y]))
		ft_error("Invalid walls");
	if (!check_char(&game->map[game->row_map_y]))
		ft_error("Invalid char");
	if (!check_top_bottom_walls(&game->map[game->row_map_y]))
		ft_error("Invalid walls top");
	fill_square_map(game, &game->map[game->row_map_y]);
	if (!map_close(game->square_map))
		ft_error("Map not close");
	printf("%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n", game->north_wall, game->south_wall, game->west_wall, game->east_wall, game->floor, game->ceiling, game->row_map_y, game->count_element);
	// print_map(game->square_map);
	return (1);
}