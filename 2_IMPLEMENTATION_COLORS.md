# 🎨 Guide d'Implémentation - Parsing des Couleurs

## 📋 Récapitulatif du Problème

Ton collègue a stocké les couleurs comme des **strings** :

```c
game->floor = "220,100,0";
game->ceiling = "225,30,0";
```

Mais pour MinilibX, il faut des **entiers hexadécimaux** :

```c
game->floor_color = 0x00DC6400;    // RGB(220, 100, 0)
game->ceiling_color = 0x00E11E00;  // RGB(225, 30, 0)
```

---

## 🔧 ÉTAPE 1 : Modifier la Structure `t_game`

**Fichier :** `include/game.h`

### Avant :

```c
typedef struct s_game {
    char    **map;
    char    **square_map;
    char    *north_wall;
    char    *south_wall;
    char    *east_wall;
    char    *west_wall;
    char    *floor;          // ❌ String
    char    *ceiling;        // ❌ String

    int     count_element;
    int     row_map_y;
    t_renderer  renderer;
} t_game;
```

### Après :

```c
typedef struct s_game {
    char    **map;
    char    **square_map;
    char    *north_wall;
    char    *south_wall;
    char    *east_wall;
    char    *west_wall;

    // Nouvelles variables pour les couleurs
    int     floor_color;     // ✅ Couleur hexa (ex: 0x00DC6400)
    int     ceiling_color;   // ✅ Couleur hexa (ex: 0x00E11E00)

    int     count_element;
    int     row_map_y;
    t_renderer  renderer;
} t_game;
```

---

## 🔧 ÉTAPE 2 : Créer la Fonction `parse_color()`

**Nouveau fichier :** `src/parsing/parse_color.c`

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vous <vous@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:00:00 by vous              #+#    #+#             */
/*   Updated: 2025/12/01 12:00:00 by vous             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Libère un tableau de chaînes (résultat de ft_split)
 */
static void free_split(char **split)
{
    int i;

    if (!split)
        return;
    i = 0;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}

/**
 * Compte le nombre d'éléments dans un tableau de chaînes
 */
static int count_split(char **split)
{
    int count;

    count = 0;
    while (split[count])
        count++;
    return (count);
}

/**
 * Vérifie qu'une string ne contient que des chiffres
 */
static int is_numeric(char *str)
{
    int i;

    i = 0;
    if (!str || !str[0])
        return (0);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

/**
 * Convertit une chaîne "R,G,B" en valeur hexadécimale 0x00RRGGBB
 *
 * Exemple :
 *   Input:  "220,100,0"
 *   Output: 0x00DC6400
 *
 * Retourne -1 en cas d'erreur
 */
int parse_color(char *color_str)
{
    char    **rgb;
    int     r;
    int     g;
    int     b;
    int     color;

    if (!color_str)
        return (-1);

    // Split par ','
    rgb = ft_split(color_str, ',');
    if (!rgb)
        return (-1);

    // Vérifier qu'il y a exactement 3 éléments
    if (count_split(rgb) != 3)
        return (free_split(rgb), -1);

    // Vérifier que ce sont bien des nombres
    if (!is_numeric(rgb[0]) || !is_numeric(rgb[1]) || !is_numeric(rgb[2]))
        return (free_split(rgb), -1);

    // Convertir en int
    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);

    // Libérer le tableau split
    free_split(rgb);

    // Vérifier les limites (0-255)
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (-1);

    // Calculer la couleur finale : 0x00RRGGBB
    color = (r << 16) | (g << 8) | b;

    return (color);
}
```

---

## 🔧 ÉTAPE 3 : Ajouter le Prototype dans `parsing.h`

**Fichier :** `include/parsing.h`

```c
#ifndef PARSING_H
# define PARSING_H

int     parsing(t_game *game, char **av);
char    **create_map(char *file);
int     fill_elements(t_game *game);
int     check_char(char **map);
int     check_left_wall(char **map);
int     check_top_bottom_walls(char **map);
int     map_close(char **map);
void    fill_square_map(t_game *game, char **map);
void    print_map(char **map);

// Nouvelle fonction
int     parse_color(char *color_str);  // ✅ Ajouter cette ligne

#endif
```

---

## 🔧 ÉTAPE 4 : Modifier `fill_elements.c`

**Fichier :** `src/parsing/fill_elements.c`

### Modifier la fonction `parse_element()` :

```c
static int parse_element(t_game *g, char *str, int *x)
{
    char *temp_color;

    if (!strncmp(&str[*x], "NO", 2))
        return (assign_value(&g->north_wall, str, x, 2), g->count_element++, 1);
    if (!strncmp(&str[*x], "SO", 2))
        return (assign_value(&g->south_wall, str, x, 2), g->count_element++, 1);
    if (!strncmp(&str[*x], "WE", 2))
        return (assign_value(&g->west_wall, str, x, 2), g->count_element++, 1);
    if (!strncmp(&str[*x], "EA", 2))
        return (assign_value(&g->east_wall, str, x, 2), g->count_element++, 1);

    // ✅ Modifier la partie Floor
    if (str[*x] == 'F')
    {
        assign_value(&temp_color, str, x, 1);
        g->floor_color = parse_color(temp_color);
        free(temp_color);
        if (g->floor_color == -1)
            return (0);  // Erreur de parsing
        g->count_element++;
        return (1);
    }

    // ✅ Modifier la partie Ceiling
    if (str[*x] == 'C')
    {
        assign_value(&temp_color, str, x, 1);
        g->ceiling_color = parse_color(temp_color);
        free(temp_color);
        if (g->ceiling_color == -1)
            return (0);  // Erreur de parsing
        g->count_element++;
        return (1);
    }

    return (0);
}
```

---

## 🔧 ÉTAPE 5 : Modifier `parsing.c`

**Fichier :** `src/parsing/parsing.c`

### Modifier `init_struct()` :

```c
static void init_struct(t_game *game)
{
    game->map = NULL;
    game->square_map = NULL;
    game->ceiling_color = -1;      // ✅ Modifier
    game->east_wall = NULL;
    game->floor_color = -1;        // ✅ Modifier
    game->north_wall = NULL;
    game->south_wall = NULL;
    game->west_wall = NULL;
    game->row_map_y = -1;
    game->count_element = 0;
}
```

### Modifier `check_elements_valid()` :

```c
static int check_elements_valid(t_game *g)
{
    if (g->count_element != 6)
        return (0);
    if (!g->north_wall || !g->south_wall || !g->west_wall || !g->east_wall)
        return (0);
    // ✅ Modifier : vérifier les couleurs au lieu des strings
    if (g->floor_color == -1 || g->ceiling_color == -1)
        return (0);
    if (g->row_map_y == -1)
        return (0);
    return (1);
}
```

### Modifier la fin de `parsing()` pour le debug :

```c
int parsing(t_game *game, char **av)
{
    init_struct(game);
    if (!check_file_cub(av[1]))
        ft_error("file is not a .cub");
    game->map = create_map(av[1]);
    if (!game->map)
        ft_error("void map");
    if (!fill_elements(game))
        ft_error("Invalid map");
    if (!check_elements_valid(game))
        ft_error("Invalid map");
    if (!check_left_wall(&game->map[game->row_map_y]))
        ft_error("Invalid walls");
    if (!check_char(&game->map[game->row_map_y]))
        ft_error("Invalid char");
    if (!check_top_bottom_walls(&game->map[game->row_map_y]))
        ft_error("Invalid walls top");
    fill_square_map(game, &game->map[game->row_map_y]);
    if (!map_close(game->square_map))
        ft_error("Map not close");

    // ✅ Debug : afficher les couleurs parsées
    printf("North: %s\n", game->north_wall);
    printf("South: %s\n", game->south_wall);
    printf("West: %s\n", game->west_wall);
    printf("East: %s\n", game->east_wall);
    printf("Floor color: 0x%06X\n", game->floor_color);      // Affiche en hexa
    printf("Ceiling color: 0x%06X\n", game->ceiling_color);  // Affiche en hexa
    printf("Map starts at line: %d\n", game->row_map_y);

    return (1);
}
```

---

## 🔧 ÉTAPE 6 : Mettre à Jour le Makefile

**Fichier :** `Makefile`

Ajouter `src/parsing/parse_color.c` aux sources :

```makefile
SRCS = src/main.c \
       src/parsing/parsing.c \
       src/parsing/create_map.c \
       src/parsing/fill_elements.c \
       src/parsing/check_char_map.c \
       src/parsing/check_close.c \
       src/parsing/parse_color.c \    # ✅ Ajouter cette ligne
       # ... autres fichiers
```

---

## 🧪 ÉTAPE 7 : Tester

### Compiler :

```bash
make re
```

### Tester avec le fichier d'exemple :

```bash
./cub3d maps/map_subject.cub
```

### Résultat attendu :

```
North: ./path_to_the_north_texture
South: ./path_to_the_south_texture
West: ./path_to_the_west_texture
East: ./path_to_the_east_texture
Floor color: 0xDC6400        # 220,100,0 → hexa
Ceiling color: 0xE11E00      # 225,30,0 → hexa
Map starts at line: 8
```

---

## ✅ Tests à Faire

### Test 1 : Couleurs valides

```
F 220,100,0    ✅
C 225,30,0     ✅
```

### Test 2 : Couleurs limites

```
F 0,0,0        ✅ (noir)
C 255,255,255  ✅ (blanc)
```

### Test 3 : Erreurs à détecter

```
F 256,100,0    ❌ (R > 255)
F -1,100,0     ❌ (R < 0)
F 220,100      ❌ (manque B)
F 220,100,0,5  ❌ (trop d'éléments)
F abc,100,0    ❌ (pas un nombre)
```

---

## 🎯 Résumé des Modifications

| Fichier                       | Action                                                              |
| ----------------------------- | ------------------------------------------------------------------- |
| `include/game.h`              | Remplacer `char *floor/ceiling` par `int floor_color/ceiling_color` |
| `src/parsing/parse_color.c`   | ✅ Créer ce fichier                                                 |
| `include/parsing.h`           | Ajouter prototype `parse_color()`                                   |
| `src/parsing/fill_elements.c` | Modifier `parse_element()` pour utiliser `parse_color()`            |
| `src/parsing/parsing.c`       | Modifier `init_struct()` et `check_elements_valid()`                |
| `Makefile`                    | Ajouter `parse_color.c` aux sources                                 |

---

## 🚀 Utilisation dans le Rendu

Une fois les couleurs parsées, tu pourras les utiliser avec MinilibX :

```c
// Dessiner un pixel avec la couleur du sol
mlx_pixel_put(mlx_ptr, win_ptr, x, y, game->floor_color);

// Ou remplir un buffer d'image
((int *)img_data)[y * width + x] = game->floor_color;
```

---

## 📚 Formule de Conversion RGB → Hexa

```
Couleur finale = (R << 16) | (G << 8) | B

Exemple avec F 220,100,0 :
R = 220 = 0xDC
G = 100 = 0x64
B = 0   = 0x00

Calcul :
0xDC << 16 = 0x00DC0000
0x64 << 8  = 0x00006400
0x00       = 0x00000000
                OR
           = 0x00DC6400
```

---

## ✨ Bon Code !

Tu as maintenant tout ce qu'il faut pour implémenter le parsing des couleurs ! 🎨🚀
