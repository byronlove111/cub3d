#ifndef UTILS_H
# define UTILS_H

/* Forward declarations */
typedef struct s_game	t_game;
typedef struct s_app	t_app;

/* Error handling */
void	ft_error(char *error);

/* Memory cleanup */
void	free_game(t_game *game);
void	cleanup_and_exit(t_app *app);

#endif