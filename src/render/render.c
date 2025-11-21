/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:58:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/11/21 15:18:19 by abbouras         ###   ########.fr       */
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

/*
	hub function to render the game
	@param renderer: the renderer
	@return 0 on success, 1 on error
*/
int	render(t_renderer *renderer)
{
	init_minilibx(renderer);
	init_window(renderer);
	mlx_loop(renderer->mlx_ptr);
	return (0);
}