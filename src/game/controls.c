/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:00:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/12/10 16:48:05 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** Callback appelé quand une touche est pressée
** Gère les déplacements et rotations du joueur
*/
int	handle_keypress(int keycode, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (keycode == KEY_ESC)
		close_game(app);
	else if (keycode == KEY_W || keycode == KEY_S)
	{
		move_forward_backward(app->game, keycode);
		redraw_scene(app);
	}
	else if (keycode == KEY_A || keycode == KEY_D)
	{
		move_strafe(app->game, keycode);
		redraw_scene(app);
	}
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
	{
		rotate_player(app->game, keycode);
		redraw_scene(app);
	}
	return (0);
}

/*
** Callback appelé quand on ferme la fenêtre (croix rouge)
** ou quand on appuie sur ESC
*/
int	close_game(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	ft_putstr_fd("Fermeture du jeu...\n", 1);
	cleanup_and_exit(app);
	return (0);
}
