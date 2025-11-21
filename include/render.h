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

/*
** ============================================================================
** FONCTIONS
** ============================================================================
*/

int	render(t_renderer *renderer);

#endif