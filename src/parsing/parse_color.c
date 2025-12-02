/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:00:00 by abbouras         #+#    #+#             */
/*   Updated: 2025/12/02 12:00:00 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Libère un tableau de chaînes (résultat de ft_split)
 */
static void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/**
 * Compte le nombre d'éléments dans un tableau de chaînes
 */
static int	count_split(char **split)
{
	int	count;

	count = 0;
	while (split[count])
		count++;
	return (count);
}

/**
 * Vérifie qu'une string ne contient que des chiffres
 */
static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * Convertit une chaîne "R,G,B" en valeur hexadécimale 0x00RRGGBB
 *
 * Exemple :
 *   Input:  "220,100,0"
 *   Output: 0x00DC6400
 *
 * Retourne -1 en cas d'erreur
 */
int	parse_color(char *color_str)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;
	int		color;

	if (!color_str)
		return (-1);
	rgb = ft_split(color_str, ',');
	if (!rgb)
		return (-1);
	if (count_split(rgb) != 3)
		return (free_split(rgb), -1);
	if (!is_numeric(rgb[0]) || !is_numeric(rgb[1]) || !is_numeric(rgb[2]))
		return (free_split(rgb), -1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_split(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	color = (r << 16) | (g << 8) | b;
	return (color);
}

