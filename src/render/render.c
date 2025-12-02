/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:58:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/12/02 11:57:37 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	init_minilibx(t_renderer *renderer)
{
	renderer->mlx_ptr = mlx_init();
	if (!renderer->mlx_ptr)
		ft_error("mlx_init failed");
}

static void	init_window(t_renderer *renderer)
{
	renderer->mlx_win = mlx_new_window(renderer->mlx_ptr, 800, 600, "Cub3d");
	if (!renderer->mlx_win)
		ft_error("mlx_new_window failed");
}

static void init_image(t_renderer *renderer, t_image *img)
{
	img->width = 800;
	img->height = 600;
	img->img = mlx_new_image(renderer->mlx_ptr, img->width, img->height);
	if (!img->img)
		ft_error("mlx_new_image failed");
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
		&img->endian);
}

/*
	hub function to render the game
	@param renderer: the renderer
	@param game: the game data (map, textures, colors, etc.)
	@return 0 on success, 1 on error
*/
int	render(t_renderer *renderer, t_game *game)
{
	t_image	img;
	t_rect square;

	(void)game;  // Paramètre pas encore utilisé, mais prêt pour le raycasting
	square.x = 300;
	square.y = 400;
	square.size = 100;
	square.color = 0x00FFFF00;
	
	init_minilibx(renderer);
	init_window(renderer);
	init_image(renderer, &img);
	
	draw_player(&img, game);
	// Exemple : Le renderer peut maintenant accéder aux données du game
	// printf("Map height: %d\n", game->row_map_y);
	// printf("Floor color: %s\n", game->floor);
	// printf("Ceiling color: %s\n", game->ceiling);
	
	mlx_put_image_to_window(renderer->mlx_ptr, renderer->mlx_win, img.img, 0, 0);
	mlx_loop(renderer->mlx_ptr);
	return (0);
}