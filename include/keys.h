/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:00:00 by abbouras          #+#    #+#             */
/*   Updated: 2025/12/09 16:08:02 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

/*
** ============================================================================
** KEYCODES - MACOS vs LINUX
** ============================================================================
*/

# ifdef __APPLE__
/* macOS keycodes */
#  define KEY_W			13
#  define KEY_A			0
#  define KEY_S			1
#  define KEY_D			2
#  define KEY_ESC		53
#  define KEY_LEFT		123
#  define KEY_RIGHT		124
#  define KEY_DOWN		125
#  define KEY_UP		126
# else
/* Linux keycodes */
#  define KEY_W			119
#  define KEY_A			97
#  define KEY_S			115
#  define KEY_D			100
#  define KEY_ESC		65307
#  define KEY_LEFT		65361
#  define KEY_RIGHT		65363
#  define KEY_DOWN		65364
#  define KEY_UP		65362
# endif

/*
** ============================================================================
** MLX EVENT CODES
** ============================================================================
*/

# define EVENT_KEY_PRESS		2
# define EVENT_KEY_RELEASE		3
# define EVENT_DESTROY_NOTIFY	17

/*
** ============================================================================
** MLX EVENT MASKS
** ============================================================================
*/

# define KEY_PRESS_MASK		(1L<<0)
# define KEY_RELEASE_MASK	(1L<<1)

#endif
