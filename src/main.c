#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	t_game		game;
	t_renderer	renderer;

	if (ac != 2)
		ft_error("Usage: ./cub3d <map_file>");
	parsing(&game, av);
	render(&renderer, &game);  // Communication : on passe game au renderer
	return (0);
}