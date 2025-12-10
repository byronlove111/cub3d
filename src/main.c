#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	t_game		game;
	t_renderer	renderer;
	t_app		app;

	if (ac != 2)
		ft_error("Usage: ./cub3d <map_file>");
	parsing(&game, av);
	init_game(&game);
	app.game = &game;
	app.renderer = &renderer;
	render(&app);
	return (0);
}