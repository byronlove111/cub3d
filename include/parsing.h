#ifndef PARSING_H
# define PARSING_H

int		parsing(t_game *game, char **av);
char	**create_map(char *file);
int		fill_elements(t_game *game, int *count_element, int *row_map_y);
int		check_char(char **map);
int		check_left_wall(char **map);
int		check_top_bottom_walls(char **map);
int		map_close(char **map);
void	fill_square_map(t_game *game, char **map);
void	print_map(char **map);
int		parse_color(char *color_str);
void	find_player_position(t_game *game, char **map);

#endif