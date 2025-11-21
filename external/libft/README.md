# Libft

Libft is a library of standard C functions implemented from scratch as part of the 42 School curriculum. It includes a variety of functions for string manipulation, memory management, character checking, and more.
The purpose of this project is to recreate many of the standard C library functions to gain a deeper understanding of their inner workings and to improve our programming skills. This project helped me in learning:
- Memory allocation and management.
- String and character manipulation.
- Linked list operations.
- Handling different data types.
- Creating a reusable library of functions.

## Table of Contents

- [Getting Started](#getting-started)
- [Functions](#functions)
- [Compilation](#compilation)
- [Usage](#usage)

## Getting Started

To get a local copy up and running, follow these simple steps.

### Prerequisites

- GCC (GNU Compiler Collection)
- Make

### Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/libft.git
    cd libft
    ```

2. Build the library:
    ```sh
    make
    ```

## Functions

Libft includes the following categories of functions:

### Character Checking

- `ft_isalnum`
- `ft_isalpha`
- `ft_isascii`
- `ft_isdigit`
- `ft_isprint`

### Conversion

- `ft_atoi`
- `ft_itoa`
- `ft_tolower`
- `ft_toupper`

### Linked List

- `ft_lstadd_back`
- `ft_lstadd_front`
- `ft_lstclear`
- `ft_lstdelone`
- `ft_lstiter`
- `ft_lstlast`
- `ft_lstmap`
- `ft_lstnew`
- `ft_lstsize`

### Memory

- `ft_bzero`
- `ft_calloc`
- `ft_memchr`
- `ft_memcmp`
- `ft_memcpy`
- `ft_memmove`
- `ft_memset`

### String

- `ft_split`
- `ft_strchr`
- `ft_strdup`
- `ft_striteri`
- `ft_strjoin`
- `ft_strlcat`
- `ft_strlcpy`
- `ft_strlen`
- `ft_strmapi`
- `ft_strncmp`
- `ft_strnstr`
- `ft_strrchr`
- `ft_strtrim`
- `ft_substr`

### Write

- `ft_putchar_fd`
- `ft_putendl_fd`
- `ft_putnbr_fd`
- `ft_putstr_fd`

## Compilation

To compile the library, simply run:

```sh
make
```

## Usage
To use libft in your project, follow these steps:

1. Include the libft.h header file in your source files.
```sh
#include "libft.h"
```
2. Link library when compiling your project
```sh
cc -Wall -Wextra -Werror -L. -lft your_program.c
```
