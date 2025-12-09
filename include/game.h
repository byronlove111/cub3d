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
	char	direction;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray {
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_game {
	t_map		map;
	t_textures	textures;
	int			floor_color;
	int			ceiling_color;
	t_player	player;
}	t_game;

#endif