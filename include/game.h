#ifndef GAME_H
# define GAME_H

# include "../include/cub3d.h"

typedef struct s_textures {
	char	*north;
	char	*south;
	char	*east;
	char	*west;
}	t_textures;

typedef struct s_map {
	char	**data;
	char	**square;
	int		width;
	int		height;
}	t_map;

typedef struct s_player {
	double	pos_x;
	double	pos_y;
	char	orientation;
}	t_player;

typedef struct s_game {
	t_map		map;
	t_textures	textures;
	int			floor_color;
	int			ceiling_color;
	t_player	player;
}	t_game;

#endif