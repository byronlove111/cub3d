/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:58:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/12/09 16:08:02 by abbouras         ###   ########.fr       */
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

static void	setup_hooks(t_app *app)
{
	mlx_hook(app->renderer->mlx_win, EVENT_KEY_PRESS, KEY_PRESS_MASK,
		handle_keypress, app);
	mlx_hook(app->renderer->mlx_win, EVENT_DESTROY_NOTIFY, 0,
		close_game, app);
}

/*
	hub function to render the game
	@param app: structure contenant game et renderer
	@return 0 on success, 1 on error
*/
int	render(t_app *app)
{
	init_minilibx(app->renderer);
	init_window(app->renderer);
	init_image(app->renderer, &app->img);
	draw_player(&app->img, app->game);
	mlx_put_image_to_window(app->renderer->mlx_ptr,
		app->renderer->mlx_win, app->img.img, 0, 0);
	setup_hooks(app);
	mlx_loop(app->renderer->mlx_ptr);
	return (0);
}