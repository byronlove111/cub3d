NAME = cub3d
CC = gcc
# CC = clang
CFLAGS = -Wall -Wextra -Werror
# CFLAGS = -fsanitize=address -g 
RM = rm -f

LIBFT_DIR = external/libft
LIBFT = $(LIBFT_DIR)/libft.a

UNAME = $(shell uname)

ifeq ($(UNAME), Darwin)
MLX_DIR = external/minilibx_mms_20200219
MLX = $(MLX_DIR)/libmlx.dylib
MLX_FLAGS = -framework OpenGL -framework AppKit
MLX_COPY = cp $(MLX) .
else
MLX_DIR = external/minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -lXext -lX11 -lm -lz -L/usr/lib -L/usr/X11R6/lib
MLX_COPY =  
endif

INCLUDES = -I./include -I$(LIBFT_DIR) -I$(MLX_DIR)

OBJ_DIR = obj

SRCS = src/main.c \
       src/render/render.c \
       src/render/draw_utils.c \
       src/render/draw_square.c \
       src/utils/error.c

OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS)
	$(MLX_COPY)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/render
	mkdir -p $(OBJ_DIR)/utils

clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(RM) libmlx.dylib
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re