#ifndef GAME_H
# define GAME_H

# include "../include/cub3d.h"

typedef struct s_game {
	char	**map;
	char	**square_map;
	char	*north_wall;
	char	*south_wall;
	char	*east_wall;
	char	*west_wall;
	int		floor_color;
	int		ceiling_color;

	int		count_element;
	int		row_map_y;
}	t_game;

#endif