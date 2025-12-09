/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:00:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/12/09 16:25:24 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** Callback appelé quand une touche est pressée
** Pour l'instant, affiche juste le keycode pour debug
*/
int	handle_keypress(int keycode, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (keycode == KEY_ESC)
		close_game(app);
	else if (keycode == KEY_W)
		printf("W - Avancer\n");
	else if (keycode == KEY_S)
		printf("S - Reculer\n");
	else if (keycode == KEY_A)
		printf("A - Gauche\n");
	else if (keycode == KEY_D)
		printf("D - Droite\n");
	else if (keycode == KEY_LEFT)
		printf("Flèche gauche - Rotation gauche\n");
	else if (keycode == KEY_RIGHT)
		printf("Flèche droite - Rotation droite\n");
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
	printf("Fermeture du jeu...\n");
	(void)app;
	exit(0);
	return (0);
}
