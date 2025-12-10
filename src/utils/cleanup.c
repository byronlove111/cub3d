/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:30:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/12/10 16:48:05 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** Libère la mémoire de la carte
*/
static void	free_map(t_map *map)
{
	int	i;

	if (map->data)
	{
		i = 0;
		while (map->data[i])
		{
			free(map->data[i]);
			i++;
		}
		free(map->data);
	}
	if (map->square)
	{
		i = 0;
		while (map->square[i])
		{
			free(map->square[i]);
			i++;
		}
		free(map->square);
	}
}

/*
** Libère la mémoire des chemins de textures
*/
static void	free_textures(t_textures *textures)
{
	if (textures->north)
		free(textures->north);
	if (textures->south)
		free(textures->south);
	if (textures->east)
		free(textures->east);
	if (textures->west)
		free(textures->west);
}

/*
** Libère toute la mémoire du jeu
*/
void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_map(&game->map);
	free_textures(&game->textures);
}

/*
** Libère les ressources MLX et ferme proprement
*/
void	cleanup_and_exit(t_app *app)
{
	if (!app)
		exit(0);
	if (app->img.img && app->renderer && app->renderer->mlx_ptr)
		mlx_destroy_image(app->renderer->mlx_ptr, app->img.img);
	if (app->renderer && app->renderer->mlx_win && app->renderer->mlx_ptr)
		mlx_destroy_window(app->renderer->mlx_ptr, app->renderer->mlx_win);
	if (app->game)
		free_game(app->game);
	exit(0);
}
