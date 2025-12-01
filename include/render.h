#ifndef RENDER_H
# define RENDER_H

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

/*
** ============================================================================
** FONCTIONS
** ============================================================================
*/

int	render(t_renderer *renderer);
void	put_pixel(t_image *img, int x, int y, int color);
void	draw_square(t_image *img, t_rect rect);

#endif