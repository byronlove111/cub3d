#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	t_game		game;
	t_renderer	renderer;

	if (ac != 2)
		ft_error("Usage: ./cub3d <map_file>");
	parsing(&game, av);
	init_game(&game);
	// render(&renderer, &game);
	return (0);
}