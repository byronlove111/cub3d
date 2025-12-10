#ifndef RENDER_H
# define RENDER_H

/*
** ============================================================================
** FORWARD DECLARATIONS
** ============================================================================
*/

typedef struct s_game	t_game;

/*
** ============================================================================
** STRUCTURES
** ============================================================================
*/

typedef struct s_renderer {
	int		window_width;
	int		window_height;
	void	*mlx_ptr;
	void	*mlx_win;
}	t_renderer;

typedef struct s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
} 	t_image;

typedef struct s_rect {
	int		x;
	int		y;
	int		size;
	int		color;
}	t_rect;

typedef struct s_app {
	t_game		*game;
	t_renderer	*renderer;
	t_image		img;
}	t_app;

/*
** ============================================================================
** FONCTIONS
** ============================================================================
*/

int		render(t_app *app);
void	put_pixel(t_image *img, int x, int y, int color);
void	draw_player(t_image *img, t_game *game);
void	clear_image(t_image *img);
void	redraw_scene(t_app *app);

#endif