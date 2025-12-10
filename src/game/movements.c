/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:56:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/12/10 16:48:05 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** Vérifie si une position est valide (pas dans un mur)
*/
int	is_valid_position(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0)
		return (0);
	if (map_y >= game->map.height || map_x >= game->map.width)
		return (0);
	if (game->map.square[map_y][map_x] == '1')
		return (0);
	return (1);
}

/*
** Déplace le joueur vers l'avant (W) ou l'arrière (S)
*/
void	move_forward_backward(t_game *game, int keycode)
{
	double	new_x;
	double	new_y;

	(void)new_x;
	(void)new_y;
	if (keycode == KEY_W)
	{
		new_x = game->player.pos_x + game->player.dir_x * MOVE_SPEED;
		new_y = game->player.pos_y + game->player.dir_y * MOVE_SPEED;
	}
	else
	{
		new_x = game->player.pos_x - game->player.dir_x * MOVE_SPEED;
		new_y = game->player.pos_y - game->player.dir_y * MOVE_SPEED;
	}
	if (is_valid_position(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_valid_position(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

/*
** Déplace le joueur latéralement (strafe A/D)
** Utilise le plan de caméra (perpendiculaire à la direction)
*/
void	move_strafe(t_game *game, int keycode)
{
	double	new_x;
	double	new_y;

	(void)new_x;
	(void)new_y;
	if (keycode == KEY_A)
	{
		new_x = game->player.pos_x - game->player.plane_x * MOVE_SPEED;
		new_y = game->player.pos_y - game->player.plane_y * MOVE_SPEED;
	}
	else
	{
		new_x = game->player.pos_x + game->player.plane_x * MOVE_SPEED;
		new_y = game->player.pos_y + game->player.plane_y * MOVE_SPEED;
	}
	if (is_valid_position(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_valid_position(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

/*
** Fait tourner le joueur (rotation gauche/droite)
** Applique une matrice de rotation sur les vecteurs dir et plane
*/
void	rotate_player(t_game *game, int keycode)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = ROT_SPEED;
	if (keycode == KEY_LEFT)
		rot_speed = -rot_speed;
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rot_speed)
		- game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed)
		+ game->player.dir_y * cos(rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rot_speed)
		- game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed)
		+ game->player.plane_y * cos(rot_speed);
}
