/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:06:33 by mehdi             #+#    #+#             */
/*   Updated: 2025/12/09 10:57:28 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_struct(t_game *game)
{
	game->map.data = NULL;
	game->map.square = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->textures.north = NULL;
	game->textures.south = NULL;
	game->textures.east = NULL;
	game->textures.west = NULL;
	game->floor_color = -1;
	game->ceiling_color = -1;
	game->player.pos_x = 0;
	game->player.pos_y = 0;
	game->player.orientation = '\0';
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

static int	check_elements_valid(t_game *g, int count_element, int row_map_y)
{
	if (count_element != 6)
		return (0);
	if (!g->textures.north || !g->textures.south
		|| !g->textures.west || !g->textures.east)
		return (0);
	if (g->floor_color == -1 || g->ceiling_color == -1)
		return (0);
	if (row_map_y == -1)
		return (0);
	return (1);
}

int	parsing(t_game *game, char **av)
{
	int	count_element;
	int	row_map_y;

	init_struct(game);
	if (!check_file_cub(av[1]))
		ft_error("file is not a .cub");
	game->map.data = create_map(av[1]);
	if (!game->map.data)
		ft_error("void map");
	if (!fill_elements(game, &count_element, &row_map_y))
		ft_error("Invalid map");
	if (!check_elements_valid(game, count_element, row_map_y))
		ft_error("Invalid map");
	if (!check_left_wall(&game->map.data[row_map_y]))
		ft_error("Invalid walls");
	if (!check_char(&game->map.data[row_map_y]))
		ft_error("Invalid char");
	find_player_position(game, &game->map.data[row_map_y]);
	if (!check_top_bottom_walls(&game->map.data[row_map_y]))
		ft_error("Invalid walls top");
	fill_square_map(game, &game->map.data[row_map_y]);
	if (!map_close(game->map.square))
		ft_error("Map not close");
	return (1);
}