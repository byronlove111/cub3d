/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:45:25 by abbouras          #+#    #+#             */
/*   Updated: 2024/11/16 13:26:22 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

// Fonctions ft_printf
size_t	_strlen(const char *s);
int		ft_printf(const char *str, ...);
void	_putchar_fd(char c, int fd, int *ct);
void	_putstr_fd(char *s, int fd, int *ct);
void	_putnbr_fd(int n, int fd, int *ct);
void	_putnbr_base_ul(unsigned long nbr, char *base, int *ct);

// Fonctions get_next_line
size_t	__strlen(const char *s);
char	*_strchr(const char *s, int c);
void	*_calloc(size_t elementCount, size_t elementSize);
char	*_strjoin(char const *s1, char const *s2);
char	*read_and_store_buffer(int fd, char *res);
char	*get_next_line(int fd);
char	*extract_current_line(char *buffer);
char	*extract_stash(char *buffer);
char	*join_and_free(char *stash, char *buffer);

// Fonctions libft
void	ft_bzero(void *s, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t elementCount, size_t elementSize);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlen(const char *str);
int		ft_atoi(const char *str);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_lstsize(t_list *lst);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, unsigned int size);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int nb);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
t_list	*ft_lstnew(void	*content);
t_list	*ft_lstlast(t_list *lst);

#endif
