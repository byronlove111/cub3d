/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 10:34:17 by mehdi             #+#    #+#             */
/*   Updated: 2025/12/01 11:49:51 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	count_lines(char *file)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

char	**create_map(char *file)
{
	int		fd;
	int		n;
	int		i;
	char	*line;
	char	**map;

	n = count_lines(file);
	if (n <= 0)
		return (NULL);
	map = malloc(sizeof(char *) * (n + 1));
	if (!map)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (free(map), NULL);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		map[i++] = line;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

// static char	**create_map(char *file)
// {
// 	int		fd;
// 	char	*line;
// 	char	*map_line;
// 	char	**map;

// 	map_line = ft_strdup("");
// 	if (!map_line)
// 		return (NULL);
// 	fd = open(file, O_RDONLY);
// 	if (fd < 0)
// 		return (free(map_line), NULL);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		map_line = join_and_free(map_line, line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	free(line);
// 	line = NULL;
// 	close(fd);
// 	map = ft_split(map_line, '\n');
// 	return (free(map_line), map);
// }