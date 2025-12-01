#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		ft_error("Usage: ./cub3d <map_file>");
	parsing(&game, av);
	render(&game.renderer);
	return (0);
}