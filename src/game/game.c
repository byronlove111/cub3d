/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:13:54 by abbouras          #+#    #+#             */
/*   Updated: 2025/12/09 15:44:41 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_game(t_game *game)
{
	printf("pos X: %f\n", game->player.pos_x);
	printf("pos Y: %f\n", game->player.pos_y);
	printf("pos Y: %c\n", game->player.direction);
	init_player_direction(&game->player);
}