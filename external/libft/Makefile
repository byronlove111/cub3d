# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/16 15:48:01 by abbouras          #+#    #+#              #
#    Updated: 2025/06/24 12:14:13 by abbouras         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC
AR = ar -rcs

NAME = libft.a

SRC = ./ft_atoi.c ./ft_bzero.c ./ft_calloc.c ./ft_isalnum.c ./ft_isalpha.c \
      ./ft_isascii.c ./ft_isdigit.c ./ft_isprint.c ./ft_memchr.c ./ft_memcmp.c \
      ./ft_memcpy.c ./ft_memmove.c ./ft_memset.c ./ft_strchr.c ./ft_strdup.c \
      ./ft_strlcat.c ./ft_strlcpy.c ./ft_strlen.c ./ft_strncmp.c ./ft_strnstr.c \
      ./ft_strrchr.c ./ft_tolower.c ./ft_toupper.c ./ft_substr.c ./ft_strjoin.c \
      ./ft_strtrim.c ./ft_split.c ./ft_putchar_fd.c ./ft_putendl_fd.c \
      ./ft_putstr_fd.c ./ft_putnbr_fd.c ./ft_itoa.c ./ft_strmapi.c ./ft_striteri.c \
      ./ft_printf/ft_printf.c ./ft_printf/utils.c \
      ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c

BONUS = ./ft_lstnew_bonus.c ./ft_lstadd_front_bonus.c ./ft_lstsize_bonus.c \
        ./ft_lstlast_bonus.c ./ft_lstadd_back_bonus.c ./ft_lstdelone_bonus.c \
        ./ft_lstclear_bonus.c ./ft_lstiter_bonus.c ./ft_lstmap_bonus.c

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS:.c=.o)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -I. -c $< -o ${<:.c=.o}

bonus: $(NAME) $(BONUS_OBJ)
	$(AR) $(NAME) $(BONUS_OBJ)

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus