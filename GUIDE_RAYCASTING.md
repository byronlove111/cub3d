# 🎮 Guide Complet du Raycasting pour cub3D

## 📚 Table des matières

1. [Introduction au Raycasting](#1-introduction-au-raycasting)
2. [Concepts Fondamentaux](#2-concepts-fondamentaux)
3. [Architecture de Notre Code](#3-architecture-de-notre-code)
4. [Étape 1 : Initialisation du Joueur](#4-étape-1--initialisation-du-joueur)
5. [Étape 2 : La Boucle de Rendu](#5-étape-2--la-boucle-de-rendu)
6. [Étape 3 : L'Algorithme DDA](#6-étape-3--lalgorithme-dda)
7. [Étape 4 : Calcul des Hauteurs de Murs](#7-étape-4--calcul-des-hauteurs-de-murs)
8. [Étape 5 : Ajout des Textures](#8-étape-5--ajout-des-textures)
9. [Étape 6 : Gestion des Contrôles](#9-étape-6--gestion-des-contrôles)
10. [Optimisations et Astuces](#10-optimisations-et-astuces)
11. [Checklist Finale](#11-checklist-finale)

---

## 1. Introduction au Raycasting

### Qu'est-ce que le raycasting ?

Le raycasting est une technique de rendu **pseudo-3D** qui crée l'illusion d'un environnement 3D à partir d'une carte 2D. C'est la technique utilisée dans **Wolfenstein 3D** (1992).

**Principe de base :**

- Vous avez une carte 2D (grille de 0 et 1)
- Pour chaque colonne de l'écran, vous lancez un "rayon" depuis le joueur
- Le rayon avance jusqu'à toucher un mur
- La distance au mur détermine la hauteur à dessiner à l'écran

### Pourquoi c'est rapide ?

Au lieu de calculer chaque pixel individuellement, on calcule seulement **une ligne verticale par colonne d'écran**. Pour un écran de 800px de large, on fait seulement 800 calculs de rayons !

### Différence avec le raytracing

- **Raycasting** : Technique 2D rapide, pas de réflexions, pas d'ombres complexes
- **Raytracing** : Technique 3D réaliste avec réflexions, ombres, etc. (beaucoup plus lent)

---

## 2. Concepts Fondamentaux

### 2.1 Le système de coordonnées

```
Votre carte 2D :
    X →
Y   1 1 1 1 1
↓   1 0 0 0 1
    1 0 P 0 1    (P = joueur)
    1 0 0 0 1
    1 1 1 1 1
```

- `0` = espace vide (on peut marcher)
- `1` = mur
- Position du joueur : coordonnées flottantes (ex: 2.5, 2.5)

### 2.2 Les vecteurs : Direction et Plan de Caméra

**Vecteur de direction (dir)** : Vers où regarde le joueur

```
Si le joueur regarde vers le NORD :
dirX = 0
dirY = -1
```

**Vecteur du plan de caméra (plane)** : Représente l'écran

```
Le plan est PERPENDICULAIRE à la direction
Si dir = (0, -1), alors plane = (0.66, 0)
```

**Pourquoi 0.66 ?**
Le ratio `longueur(plane) / longueur(dir)` détermine le FOV (Field of View).

- FOV = 2 × atan(0.66/1.0) ≈ 66° (parfait pour un FPS)

### 2.3 Calcul de la direction d'un rayon

Pour chaque colonne `x` de l'écran :

```c
// Normaliser x entre -1 (gauche) et +1 (droite)
cameraX = 2 * x / screenWidth - 1;

// Direction du rayon = direction + partie du plan
rayDirX = dirX + planeX * cameraX;
rayDirY = dirY + planeY * cameraX;
```

**Exemple visuel :**

```
        plane
    ←----------→
    |          |
    |    dir   |
    |     ↑    |
    |     |    |
    |     P    |  (P = joueur)

Les rayons partent de P et traversent le plan
```

### 2.4 L'algorithme DDA (Digital Differential Analysis)

**Problème :** Comment trouver le premier mur qu'un rayon touche ?

**Mauvaise solution :** Avancer le rayon par petits pas constants

- Risque de manquer des murs
- Beaucoup de calculs

**Bonne solution (DDA) :** Sauter directement d'une case de la grille à la suivante

```
    |   |   |   |
    | 0 | 1 | 0 |
    |   | X |   |
    -----+-------
    | 0 | 0 | 0 |
    |   |   |   |

Le rayon saute aux intersections de la grille (marquées +)
```

### 2.5 Éviter l'effet Fisheye

**Problème :** Si on utilise la distance euclidienne, les murs deviennent arrondis.

**Solution :** Utiliser la distance **perpendiculaire au plan de caméra**

```
        Mur
         |
    A----+----B
         |
    ←----P    (P = joueur, plan de caméra = ligne AB)

On utilise la distance perpendiculaire, pas la distance directe
```

---

## 3. Architecture de Notre Code

### 3.1 Structures existantes

Voici ce que vous avez déjà dans `include/game.h` :

```c
typedef struct s_player {
    double  pos_x;      // Position X du joueur
    double  pos_y;      // Position Y du joueur
    char    dir;        // Direction : 'N', 'S', 'E', 'W'
} t_player;

typedef struct s_game {
    t_map       map;
    t_textures  textures;
    int         floor_color;
    int         ceiling_color;
    t_player    player;
} t_game;
```

### 3.2 Ce qu'il faut ajouter

**Dans `t_player` :**

```c
typedef struct s_player {
    double  pos_x;
    double  pos_y;
    char    dir;        // On garde pour le parsing

    // NOUVEAUX CHAMPS pour le raycasting
    double  dir_x;      // Vecteur direction X
    double  dir_y;      // Vecteur direction Y
    double  plane_x;    // Plan de caméra X
    double  plane_y;    // Plan de caméra Y
} t_player;
```

**Nouvelle structure pour le raycasting :**

```c
typedef struct s_ray {
    double  camera_x;       // Position X sur le plan de caméra
    double  dir_x;          // Direction du rayon X
    double  dir_y;          // Direction du rayon Y

    int     map_x;          // Case de la carte X
    int     map_y;          // Case de la carte Y

    double  side_dist_x;    // Distance au prochain côté X
    double  side_dist_y;    // Distance au prochain côté Y

    double  delta_dist_x;   // Distance entre deux côtés X
    double  delta_dist_y;   // Distance entre deux côtés Y

    int     step_x;         // Direction du pas (-1 ou +1)
    int     step_y;         // Direction du pas (-1 ou +1)

    int     hit;            // Mur touché ?
    int     side;           // Côté touché (0=X, 1=Y)

    double  perp_wall_dist; // Distance perpendiculaire au mur
    int     line_height;    // Hauteur de la ligne à dessiner
    int     draw_start;     // Début du dessin
    int     draw_end;       // Fin du dessin
} t_ray;
```

### 3.3 Organisation des fichiers

```
src/
├── render/
│   ├── render.c           (existant - boucle principale)
│   ├── raycasting.c       (NOUVEAU - algorithme de raycasting)
│   ├── draw_walls.c       (NOUVEAU - dessin des murs)
│   └── draw_utils.c       (existant - fonctions utilitaires)
├── game/
│   ├── init_player.c      (NOUVEAU - initialisation du joueur)
│   ├── player_movement.c  (NOUVEAU - déplacements)
│   └── player_rotation.c  (NOUVEAU - rotations)
└── main.c
```

---

## 4. Étape 1 : Initialisation du Joueur

### 4.1 Convertir la direction du parsing en vecteurs

Créez `src/game/init_player.c` :

```c
#include "../../include/cub3d.h"

/*
** Initialise les vecteurs de direction et de plan de caméra
** selon l'orientation du joueur (N, S, E, W)
*/
void    init_player_vectors(t_player *player)
{
    if (player->dir == 'N')
    {
        player->dir_x = 0;
        player->dir_y = -1;
        player->plane_x = 0.66;
        player->plane_y = 0;
    }
    else if (player->dir == 'S')
    {
        player->dir_x = 0;
        player->dir_y = 1;
        player->plane_x = -0.66;
        player->plane_y = 0;
    }
    else if (player->dir == 'E')
    {
        player->dir_x = 1;
        player->dir_y = 0;
        player->plane_x = 0;
        player->plane_y = 0.66;
    }
    else if (player->dir == 'W')
    {
        player->dir_x = -1;
        player->dir_y = 0;
        player->plane_x = 0;
        player->plane_y = -0.66;
    }
}
```

**Explication des valeurs :**

- **Nord (N)** : On regarde "vers le haut" donc Y négatif
- **Sud (S)** : On regarde "vers le bas" donc Y positif
- **Est (E)** : On regarde "vers la droite" donc X positif
- **Ouest (W)** : On regarde "vers la gauche" donc X négatif
- Le plan est toujours perpendiculaire à la direction

### 4.2 Appeler l'initialisation

Dans `src/parsing/parsing.c`, après `find_player_position()` :

```c
int parsing(t_game *game, char **av)
{
    // ... code existant ...

    find_player_position(game, &game->map.data[row_map_y]);

    // NOUVEAU : Initialiser les vecteurs du joueur
    init_player_vectors(&game->player);

    // ... reste du code ...
}
```

---

## 5. Étape 2 : La Boucle de Rendu

### 5.1 Structure de la boucle principale

Modifiez `src/render/render.c` :

```c
#include "../../include/cub3d.h"

/*
** Dessine le sol et le plafond
*/
static void draw_floor_ceiling(t_image *img, t_game *game)
{
    int x;
    int y;

    // Dessiner le plafond (moitié supérieure)
    y = 0;
    while (y < img->height / 2)
    {
        x = 0;
        while (x < img->width)
        {
            put_pixel(img, x, y, game->ceiling_color);
            x++;
        }
        y++;
    }

    // Dessiner le sol (moitié inférieure)
    while (y < img->height)
    {
        x = 0;
        while (x < img->width)
        {
            put_pixel(img, x, y, game->floor_color);
            x++;
        }
        y++;
    }
}

/*
** Boucle de rendu principale
*/
int render_frame(t_renderer *renderer, t_game *game, t_image *img)
{
    // 1. Dessiner sol et plafond
    draw_floor_ceiling(img, game);

    // 2. Lancer le raycasting pour chaque colonne
    raycast(img, game);

    // 3. Afficher l'image
    mlx_put_image_to_window(renderer->mlx_ptr, renderer->mlx_win,
                            img->img, 0, 0);
    return (0);
}

/*
** Point d'entrée du rendu
*/
int render(t_renderer *renderer, t_game *game)
{
    t_image img;

    init_minilibx(renderer);
    init_window(renderer);
    init_image(renderer, &img);

    // Boucle de rendu avec mlx_loop_hook
    mlx_loop_hook(renderer->mlx_ptr, render_frame, /* params */);

    mlx_loop(renderer->mlx_ptr);
    return (0);
}
```

**Note :** Vous devrez adapter `mlx_loop_hook` pour passer les paramètres correctement. Une solution est de créer une structure qui contient tout :

```c
typedef struct s_render_data {
    t_renderer  *renderer;
    t_game      *game;
    t_image     *img;
} t_render_data;
```

---

## 6. Étape 3 : L'Algorithme DDA

### 6.1 Initialisation d'un rayon

Créez `src/render/raycasting.c` :

```c
#include "../../include/cub3d.h"

/*
** Initialise les valeurs de base du rayon
*/
static void init_ray(t_ray *ray, t_player *player, int x, int screen_width)
{
    // Position sur le plan de caméra (-1 à gauche, +1 à droite)
    ray->camera_x = 2.0 * x / (double)screen_width - 1.0;

    // Direction du rayon
    ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
    ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;

    // Case de la carte où se trouve le joueur
    ray->map_x = (int)player->pos_x;
    ray->map_y = (int)player->pos_y;

    // Calcul de deltaDist
    // deltaDist = distance que le rayon doit parcourir pour
    // aller d'un côté X (ou Y) au suivant
    if (ray->dir_x == 0)
        ray->delta_dist_x = 1e30;  // Valeur très grande
    else
        ray->delta_dist_x = fabs(1.0 / ray->dir_x);

    if (ray->dir_y == 0)
        ray->delta_dist_y = 1e30;
    else
        ray->delta_dist_y = fabs(1.0 / ray->dir_y);

    ray->hit = 0;
}

/*
** Calcule la direction du pas et la distance initiale
*/
static void calculate_step_and_side_dist(t_ray *ray, t_player *player)
{
    // Direction du rayon en X
    if (ray->dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x)
                           * ray->delta_dist_x;
    }

    // Direction du rayon en Y
    if (ray->dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y)
                           * ray->delta_dist_y;
    }
}
```

### 6.2 L'algorithme DDA

```c
/*
** Effectue le DDA : avance case par case jusqu'à toucher un mur
*/
static void perform_dda(t_ray *ray, t_game *game)
{
    while (ray->hit == 0)
    {
        // Avancer d'une case (soit en X, soit en Y)
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;  // Côté X touché
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;  // Côté Y touché
        }

        // Vérifier si on a touché un mur
        if (game->map.square[ray->map_y][ray->map_x] == '1')
            ray->hit = 1;
    }
}
```

**Explication du DDA :**

1. On compare `side_dist_x` et `side_dist_y`
2. On avance dans la direction la plus proche
3. On met à jour la position sur la carte
4. On vérifie si c'est un mur
5. On répète jusqu'à toucher un mur

### 6.3 Calcul de la distance perpendiculaire

```c
/*
** Calcule la distance perpendiculaire au mur
** (pour éviter l'effet fisheye)
*/
static void calculate_wall_distance(t_ray *ray)
{
    if (ray->side == 0)
        ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
    else
        ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
}
```

**Pourquoi cette formule ?**

- `side_dist_x` contient la distance totale parcourue
- On soustrait `delta_dist_x` pour revenir au point d'impact exact
- C'est la distance perpendiculaire au plan de caméra

---

## 7. Étape 4 : Calcul des Hauteurs de Murs

### 7.1 Calcul de la hauteur de ligne

```c
/*
** Calcule la hauteur de la ligne à dessiner et ses limites
*/
static void calculate_line_height(t_ray *ray, int screen_height)
{
    // Hauteur de la ligne = hauteur écran / distance
    ray->line_height = (int)(screen_height / ray->perp_wall_dist);

    // Point de départ (centré verticalement)
    ray->draw_start = -ray->line_height / 2 + screen_height / 2;
    if (ray->draw_start < 0)
        ray->draw_start = 0;

    // Point de fin
    ray->draw_end = ray->line_height / 2 + screen_height / 2;
    if (ray->draw_end >= screen_height)
        ray->draw_end = screen_height - 1;
}
```

**Logique :**

- Plus le mur est proche → distance petite → ligne haute
- Plus le mur est loin → distance grande → ligne basse
- On centre la ligne verticalement sur l'écran

### 7.2 Dessin d'une ligne verticale (version simple sans texture)

Créez `src/render/draw_walls.c` :

```c
#include "../../include/cub3d.h"

/*
** Choisit la couleur du mur selon le côté touché
*/
static int get_wall_color(t_ray *ray)
{
    int color;

    // Couleur de base (vous pouvez utiliser les textures plus tard)
    color = 0x00FFFFFF;  // Blanc

    // Assombrir les côtés Y pour donner un effet de profondeur
    if (ray->side == 1)
        color = color / 2;

    return (color);
}

/*
** Dessine une ligne verticale pour un rayon
*/
void draw_wall_stripe(t_image *img, t_ray *ray, int x)
{
    int     y;
    int     color;

    color = get_wall_color(ray);

    y = ray->draw_start;
    while (y <= ray->draw_end)
    {
        put_pixel(img, x, y, color);
        y++;
    }
}
```

### 7.3 Fonction principale de raycasting

Dans `src/render/raycasting.c` :

```c
/*
** Lance un rayon pour une colonne de l'écran
*/
static void cast_ray(t_image *img, t_game *game, int x)
{
    t_ray ray;

    // 1. Initialiser le rayon
    init_ray(&ray, &game->player, x, img->width);

    // 2. Calculer step et sideDist
    calculate_step_and_side_dist(&ray, &game->player);

    // 3. Effectuer le DDA
    perform_dda(&ray, game);

    // 4. Calculer la distance perpendiculaire
    calculate_wall_distance(&ray);

    // 5. Calculer la hauteur de ligne
    calculate_line_height(&ray, img->height);

    // 6. Dessiner la ligne
    draw_wall_stripe(img, &ray, x);
}

/*
** Fonction principale de raycasting
** Lance un rayon pour chaque colonne de l'écran
*/
void raycast(t_image *img, t_game *game)
{
    int x;

    x = 0;
    while (x < img->width)
    {
        cast_ray(img, game, x);
        x++;
    }
}
```

**À ce stade, vous devriez voir des murs blancs/gris !**

---

## 8. Étape 5 : Ajout des Textures

### 8.1 Charger les textures

Ajoutez dans `include/game.h` :

```c
typedef struct s_texture {
    void    *img;
    char    *addr;
    int     width;
    int     height;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
} t_texture;

typedef struct s_textures {
    char        *north;     // Chemin (existant)
    char        *south;
    char        *east;
    char        *west;

    t_texture   north_tex;  // Image chargée (NOUVEAU)
    t_texture   south_tex;
    t_texture   east_tex;
    t_texture   west_tex;
} t_textures;
```

Créez `src/render/load_textures.c` :

```c
#include "../../include/cub3d.h"

/*
** Charge une texture depuis un fichier XPM
*/
static int load_texture(void *mlx, t_texture *tex, char *path)
{
    tex->img = mlx_xpm_file_to_image(mlx, path,
                                     &tex->width, &tex->height);
    if (!tex->img)
        return (0);

    tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
                                   &tex->line_length, &tex->endian);
    return (1);
}

/*
** Charge toutes les textures du jeu
*/
int load_all_textures(t_renderer *renderer, t_game *game)
{
    if (!load_texture(renderer->mlx_ptr, &game->textures.north_tex,
                      game->textures.north))
        return (0);
    if (!load_texture(renderer->mlx_ptr, &game->textures.south_tex,
                      game->textures.south))
        return (0);
    if (!load_texture(renderer->mlx_ptr, &game->textures.east_tex,
                      game->textures.east))
        return (0);
    if (!load_texture(renderer->mlx_ptr, &game->textures.west_tex,
                      game->textures.west))
        return (0);
    return (1);
}
```

### 8.2 Calculer la position sur la texture

Dans `src/render/raycasting.c`, ajoutez :

```c
/*
** Calcule quelle texture utiliser et la coordonnée X sur la texture
*/
static void calculate_texture_x(t_ray *ray, t_game *game, t_texture **tex)
{
    double wall_x;
    int    tex_x;

    // Calculer où exactement le mur a été touché
    if (ray->side == 0)
        wall_x = game->player.pos_y + ray->perp_wall_dist * ray->dir_y;
    else
        wall_x = game->player.pos_x + ray->perp_wall_dist * ray->dir_x;

    wall_x -= floor(wall_x);  // Garder seulement la partie décimale

    // Choisir la texture selon l'orientation
    if (ray->side == 0)
    {
        if (ray->dir_x > 0)
            *tex = &game->textures.east_tex;   // Mur Est
        else
            *tex = &game->textures.west_tex;   // Mur Ouest
    }
    else
    {
        if (ray->dir_y > 0)
            *tex = &game->textures.south_tex;  // Mur Sud
        else
            *tex = &game->textures.north_tex;  // Mur Nord
    }

    // Coordonnée X sur la texture
    tex_x = (int)(wall_x * (double)(*tex)->width);

    // Inverser la texture si nécessaire
    if ((ray->side == 0 && ray->dir_x > 0) ||
        (ray->side == 1 && ray->dir_y < 0))
        tex_x = (*tex)->width - tex_x - 1;

    ray->tex_x = tex_x;
}
```

### 8.3 Dessiner avec les textures

Modifiez `src/render/draw_walls.c` :

```c
/*
** Récupère la couleur d'un pixel de texture
*/
static int get_texture_color(t_texture *tex, int x, int y)
{
    char *pixel;

    if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
        return (0);

    pixel = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
    return (*(int *)pixel);
}

/*
** Dessine une ligne verticale avec texture
*/
void draw_textured_wall_stripe(t_image *img, t_ray *ray, t_texture *tex, int x)
{
    int     y;
    int     tex_y;
    double  step;
    double  tex_pos;
    int     color;

    // Calcul du pas pour parcourir la texture
    step = 1.0 * tex->height / ray->line_height;

    // Position de départ sur la texture
    tex_pos = (ray->draw_start - img->height / 2 + ray->line_height / 2) * step;

    // Dessiner chaque pixel de la ligne
    y = ray->draw_start;
    while (y <= ray->draw_end)
    {
        // Coordonnée Y sur la texture
        tex_y = (int)tex_pos & (tex->height - 1);
        tex_pos += step;

        // Récupérer la couleur de la texture
        color = get_texture_color(tex, ray->tex_x, tex_y);

        // Assombrir les côtés Y
        if (ray->side == 1)
            color = (color >> 1) & 0x7F7F7F;

        put_pixel(img, x, y, color);
        y++;
    }
}
```

### 8.4 Mettre à jour la fonction de raycasting

Dans `cast_ray()` :

```c
static void cast_ray(t_image *img, t_game *game, int x)
{
    t_ray       ray;
    t_texture   *tex;

    init_ray(&ray, &game->player, x, img->width);
    calculate_step_and_side_dist(&ray, &game->player);
    perform_dda(&ray, game);
    calculate_wall_distance(&ray);
    calculate_line_height(&ray, img->height);

    // NOUVEAU : Calculer la texture et tex_x
    calculate_texture_x(&ray, game, &tex);

    // Dessiner avec texture
    draw_textured_wall_stripe(img, &ray, tex, x);
}
```

---

## 9. Étape 6 : Gestion des Contrôles

### 9.1 Définir les touches

Dans `include/game.h`, ajoutez :

```c
// Codes de touches (à adapter selon votre système)
# define KEY_W          13    // ou 119 sur Linux
# define KEY_A          0     // ou 97
# define KEY_S          1     // ou 115
# define KEY_D          2     // ou 100
# define KEY_LEFT       123   // ou 65361
# define KEY_RIGHT      124   // ou 65363
# define KEY_ESC        53    // ou 65307
```

### 9.2 Gestion des événements

Créez `src/game/events.c` :

```c
#include "../../include/cub3d.h"

/*
** Ferme le programme proprement
*/
int close_game(t_renderer *renderer)
{
    mlx_destroy_window(renderer->mlx_ptr, renderer->mlx_win);
    exit(0);
    return (0);
}

/*
** Gestion de la touche ESC et de la croix rouge
*/
int handle_keypress(int keycode, t_renderer *renderer)
{
    if (keycode == KEY_ESC)
        close_game(renderer);
    return (0);
}
```

### 9.3 Déplacements

Créez `src/game/player_movement.c` :

```c
#include "../../include/cub3d.h"

/*
** Vérifie si une position est valide (pas dans un mur)
*/
static int is_valid_position(t_game *game, double x, double y)
{
    int map_x;
    int map_y;

    map_x = (int)x;
    map_y = (int)y;

    if (map_x < 0 || map_y < 0)
        return (0);
    if (map_y >= game->map.height || map_x >= game->map.width)
        return (0);
    if (game->map.square[map_y][map_x] == '1')
        return (0);
    return (1);
}

/*
** Déplace le joueur vers l'avant
*/
void move_forward(t_game *game, double move_speed)
{
    double new_x;
    double new_y;

    new_x = game->player.pos_x + game->player.dir_x * move_speed;
    new_y = game->player.pos_y + game->player.dir_y * move_speed;

    if (is_valid_position(game, new_x, game->player.pos_y))
        game->player.pos_x = new_x;
    if (is_valid_position(game, game->player.pos_x, new_y))
        game->player.pos_y = new_y;
}

/*
** Déplace le joueur vers l'arrière
*/
void move_backward(t_game *game, double move_speed)
{
    double new_x;
    double new_y;

    new_x = game->player.pos_x - game->player.dir_x * move_speed;
    new_y = game->player.pos_y - game->player.dir_y * move_speed;

    if (is_valid_position(game, new_x, game->player.pos_y))
        game->player.pos_x = new_x;
    if (is_valid_position(game, game->player.pos_x, new_y))
        game->player.pos_y = new_y;
}

/*
** Strafe vers la gauche
*/
void strafe_left(t_game *game, double move_speed)
{
    double new_x;
    double new_y;

    // Perpendiculaire à la direction = plane
    new_x = game->player.pos_x - game->player.plane_x * move_speed;
    new_y = game->player.pos_y - game->player.plane_y * move_speed;

    if (is_valid_position(game, new_x, game->player.pos_y))
        game->player.pos_x = new_x;
    if (is_valid_position(game, game->player.pos_x, new_y))
        game->player.pos_y = new_y;
}

/*
** Strafe vers la droite
*/
void strafe_right(t_game *game, double move_speed)
{
    double new_x;
    double new_y;

    new_x = game->player.pos_x + game->player.plane_x * move_speed;
    new_y = game->player.pos_y + game->player.plane_y * move_speed;

    if (is_valid_position(game, new_x, game->player.pos_y))
        game->player.pos_x = new_x;
    if (is_valid_position(game, game->player.pos_x, new_y))
        game->player.pos_y = new_y;
}
```

### 9.4 Rotations

Créez `src/game/player_rotation.c` :

```c
#include "../../include/cub3d.h"

/*
** Fait tourner le joueur vers la gauche
*/
void rotate_left(t_game *game, double rot_speed)
{
    double old_dir_x;
    double old_plane_x;

    // Rotation du vecteur direction
    old_dir_x = game->player.dir_x;
    game->player.dir_x = game->player.dir_x * cos(rot_speed)
                       - game->player.dir_y * sin(rot_speed);
    game->player.dir_y = old_dir_x * sin(rot_speed)
                       + game->player.dir_y * cos(rot_speed);

    // Rotation du plan de caméra
    old_plane_x = game->player.plane_x;
    game->player.plane_x = game->player.plane_x * cos(rot_speed)
                         - game->player.plane_y * sin(rot_speed);
    game->player.plane_y = old_plane_x * sin(rot_speed)
                         + game->player.plane_y * cos(rot_speed);
}

/*
** Fait tourner le joueur vers la droite
*/
void rotate_right(t_game *game, double rot_speed)
{
    double old_dir_x;
    double old_plane_x;

    // Rotation inverse (angle négatif)
    old_dir_x = game->player.dir_x;
    game->player.dir_x = game->player.dir_x * cos(-rot_speed)
                       - game->player.dir_y * sin(-rot_speed);
    game->player.dir_y = old_dir_x * sin(-rot_speed)
                       + game->player.dir_y * cos(-rot_speed);

    old_plane_x = game->player.plane_x;
    game->player.plane_x = game->player.plane_x * cos(-rot_speed)
                         - game->player.plane_y * sin(-rot_speed);
    game->player.plane_y = old_plane_x * sin(-rot_speed)
                         + game->player.plane_y * cos(-rot_speed);
}
```

**Formule de rotation :**

```
Pour tourner un vecteur (x, y) d'un angle θ :
x' = x * cos(θ) - y * sin(θ)
y' = x * sin(θ) + y * cos(θ)
```

### 9.5 Intégration dans la boucle de rendu

Modifiez `src/render/render.c` :

```c
/*
** Gère les inputs et met à jour le jeu
*/
static void handle_input(t_game *game)
{
    double move_speed = 0.05;  // Vitesse de déplacement
    double rot_speed = 0.03;   // Vitesse de rotation

    // Vous devrez implémenter une fonction pour vérifier
    // si une touche est actuellement pressée
    // (avec mlx_hook ou en stockant l'état des touches)

    if (key_is_pressed(KEY_W))
        move_forward(game, move_speed);
    if (key_is_pressed(KEY_S))
        move_backward(game, move_speed);
    if (key_is_pressed(KEY_A))
        strafe_left(game, move_speed);
    if (key_is_pressed(KEY_D))
        strafe_right(game, move_speed);
    if (key_is_pressed(KEY_LEFT))
        rotate_left(game, rot_speed);
    if (key_is_pressed(KEY_RIGHT))
        rotate_right(game, rot_speed);
}

int render_frame(t_renderer *renderer, t_game *game, t_image *img)
{
    // Gérer les inputs
    handle_input(game);

    // Dessiner
    draw_floor_ceiling(img, game);
    raycast(img, game);
    mlx_put_image_to_window(renderer->mlx_ptr, renderer->mlx_win,
                            img->img, 0, 0);
    return (0);
}
```

### 9.6 Système de gestion des touches

Pour gérer les touches de manière fluide, ajoutez dans `include/game.h` :

```c
typedef struct s_keys {
    int w;
    int a;
    int s;
    int d;
    int left;
    int right;
} t_keys;
```

Ajoutez `t_keys keys;` dans `t_game`.

Créez les hooks :

```c
int key_press(int keycode, t_game *game)
{
    if (keycode == KEY_W)
        game->keys.w = 1;
    if (keycode == KEY_A)
        game->keys.a = 1;
    if (keycode == KEY_S)
        game->keys.s = 1;
    if (keycode == KEY_D)
        game->keys.d = 1;
    if (keycode == KEY_LEFT)
        game->keys.left = 1;
    if (keycode == KEY_RIGHT)
        game->keys.right = 1;
    if (keycode == KEY_ESC)
        close_game(/* ... */);
    return (0);
}

int key_release(int keycode, t_game *game)
{
    if (keycode == KEY_W)
        game->keys.w = 0;
    if (keycode == KEY_A)
        game->keys.a = 0;
    if (keycode == KEY_S)
        game->keys.s = 0;
    if (keycode == KEY_D)
        game->keys.d = 0;
    if (keycode == KEY_LEFT)
        game->keys.left = 0;
    if (keycode == KEY_RIGHT)
        game->keys.right = 0;
    return (0);
}
```

Dans `render()` :

```c
mlx_hook(renderer->mlx_win, 2, 1L<<0, key_press, game);
mlx_hook(renderer->mlx_win, 3, 1L<<1, key_release, game);
mlx_hook(renderer->mlx_win, 17, 0, close_game, renderer);
```

---

## 10. Optimisations et Astuces

### 10.1 Optimisations de performance

**1. Pré-calculer les valeurs constantes**

```c
// Au lieu de recalculer cos/sin à chaque frame
typedef struct s_player {
    // ...
    double  cos_angle;  // Pré-calculé
    double  sin_angle;
} t_player;
```

**2. Utiliser des entiers quand c'est possible**

```c
// Pour les coordonnées de texture, utilisez des int
int tex_x = (int)(wall_x * tex_width);
```

**3. Limiter les appels à mlx_put_image_to_window**

```c
// Une seule fois par frame, pas plus !
mlx_put_image_to_window(mlx, win, img, 0, 0);
```

### 10.2 Gestion des erreurs

**Vérifier les textures manquantes :**

```c
if (!tex->img)
{
    ft_putstr_fd("Error\nTexture not found\n", 2);
    exit(1);
}
```

**Vérifier les divisions par zéro :**

```c
if (ray->dir_x == 0)
    ray->delta_dist_x = 1e30;
```

### 10.3 Debug et visualisation

**Mode debug pour voir les rayons :**

```c
#define DEBUG_MODE 0

#if DEBUG_MODE
    // Dessiner la map 2D en haut à gauche
    draw_minimap(img, game);
    // Dessiner les rayons
    draw_rays(img, game);
#endif
```

### 10.4 Améliorer la collision

**Ajouter un rayon de collision :**

```c
#define COLLISION_RADIUS 0.2

static int is_valid_position(t_game *game, double x, double y)
{
    // Vérifier plusieurs points autour du joueur
    if (game->map.square[(int)(y + COLLISION_RADIUS)][(int)x] == '1')
        return (0);
    if (game->map.square[(int)(y - COLLISION_RADIUS)][(int)x] == '1')
        return (0);
    if (game->map.square[(int)y][(int)(x + COLLISION_RADIUS)] == '1')
        return (0);
    if (game->map.square[(int)y][(int)(x - COLLISION_RADIUS)] == '1')
        return (0);
    return (1);
}
```

---

## 11. Checklist Finale

### ✅ Parsing (déjà fait)

- [x] Lecture du fichier .cub
- [x] Validation de la carte
- [x] Extraction des textures et couleurs
- [x] Position du joueur

### ✅ Structures

- [ ] Ajouter `dir_x`, `dir_y`, `plane_x`, `plane_y` à `t_player`
- [ ] Créer la structure `t_ray`
- [ ] Créer la structure `t_texture` avec images chargées
- [ ] Ajouter `t_keys` pour la gestion des touches

### ✅ Initialisation

- [ ] Fonction `init_player_vectors()` pour convertir N/S/E/W
- [ ] Charger les textures avec `mlx_xpm_file_to_image()`
- [ ] Initialiser les hooks (key_press, key_release, close)

### ✅ Raycasting

- [ ] Fonction `init_ray()` - initialiser un rayon
- [ ] Fonction `calculate_step_and_side_dist()` - calculer les pas
- [ ] Fonction `perform_dda()` - algorithme DDA
- [ ] Fonction `calculate_wall_distance()` - distance perpendiculaire
- [ ] Fonction `calculate_line_height()` - hauteur de ligne
- [ ] Fonction `calculate_texture_x()` - position sur texture
- [ ] Fonction `raycast()` - boucle principale

### ✅ Rendu

- [ ] Fonction `draw_floor_ceiling()` - sol et plafond
- [ ] Fonction `draw_textured_wall_stripe()` - ligne avec texture
- [ ] Fonction `render_frame()` - boucle de rendu

### ✅ Contrôles

- [ ] Fonction `move_forward()` / `move_backward()`
- [ ] Fonction `strafe_left()` / `strafe_right()`
- [ ] Fonction `rotate_left()` / `rotate_right()`
- [ ] Fonction `is_valid_position()` - collision
- [ ] Hook pour ESC et croix rouge

### ✅ Tests

- [ ] Tester avec différentes cartes
- [ ] Vérifier les collisions
- [ ] Vérifier les textures sur tous les côtés
- [ ] Tester les rotations et déplacements
- [ ] Vérifier qu'il n'y a pas de fuites mémoire (valgrind)
- [ ] Vérifier la norminette

### ✅ Makefile

- [ ] Ajouter les nouveaux fichiers sources
- [ ] Ajouter `-lm` pour les fonctions mathématiques
- [ ] Vérifier que tout compile sans warnings

---

## 🎯 Ordre d'Implémentation Recommandé

1. **Jour 1 : Structures et initialisation**

   - Modifier `game.h` avec les nouvelles structures
   - Créer `init_player.c` et `init_player_vectors()`
   - Tester que le parsing fonctionne toujours

2. **Jour 2 : Raycasting basique**

   - Créer `raycasting.c` avec toutes les fonctions DDA
   - Dessiner des murs unis (sans texture)
   - Objectif : voir des murs blancs/gris

3. **Jour 3 : Sol et plafond**

   - Implémenter `draw_floor_ceiling()`
   - Vérifier que les couleurs du .cub sont utilisées

4. **Jour 4 : Textures**

   - Créer `load_textures.c`
   - Implémenter `calculate_texture_x()`
   - Modifier `draw_wall_stripe()` pour utiliser les textures

5. **Jour 5 : Contrôles**

   - Créer `player_movement.c` et `player_rotation.c`
   - Implémenter les hooks
   - Tester les déplacements et rotations

6. **Jour 6 : Polish et tests**
   - Améliorer les collisions
   - Tester avec différentes cartes
   - Corriger les bugs
   - Vérifier la norminette

---

## 📖 Ressources Supplémentaires

### Concepts mathématiques

- **Vecteurs** : Un vecteur (x, y) représente une direction et une magnitude
- **Produit scalaire** : `a·b = ax*bx + ay*by` (utile pour les angles)
- **Rotation** : Matrice de rotation pour tourner un vecteur

### Debugging

```c
// Afficher les valeurs pour débugger
printf("Player: (%.2f, %.2f) dir: (%.2f, %.2f)\n",
       player->pos_x, player->pos_y, player->dir_x, player->dir_y);
printf("Ray: mapX=%d mapY=%d side=%d dist=%.2f\n",
       ray->map_x, ray->map_y, ray->side, ray->perp_wall_dist);
```

### Problèmes courants

**1. Écran noir**

- Vérifiez que `raycast()` est appelé
- Vérifiez que les textures sont chargées
- Vérifiez que `mlx_put_image_to_window()` est appelé

**2. Murs déformés (fisheye)**

- Utilisez bien la distance perpendiculaire, pas euclidienne
- Formule : `perpWallDist = sideDistX - deltaDistX` (ou Y)

**3. Textures inversées**

- Vérifiez les conditions dans `calculate_texture_x()`
- Inversez `tex_x` si nécessaire

**4. Crash lors du déplacement**

- Vérifiez les limites de la carte dans `is_valid_position()`
- Ajoutez des marges de collision

**5. Rotation bizarre**

- Vérifiez que vous rotez à la fois `dir` ET `plane`
- Utilisez la bonne formule de rotation

---

## 🎉 Félicitations !

Si vous avez suivi ce guide, vous devriez maintenant avoir un raycaster fonctionnel avec :

- ✅ Rendu 3D d'un labyrinthe
- ✅ Textures sur les murs
- ✅ Sol et plafond colorés
- ✅ Déplacements fluides (WASD)
- ✅ Rotation de la caméra (flèches)
- ✅ Collisions avec les murs

**Prochaines étapes possibles (bonus) :**

- Minimap en temps réel
- Sprites (ennemis, objets)
- Portes qui s'ouvrent
- Effets de lumière
- Skybox

Bon courage pour votre projet cub3D ! 🚀

---

**Auteur :** Guide adapté pour cub3D de 42  
**Sources :** Lode's Raycasting Tutorial + RayCaster reference implementation  
**Date :** Décembre 2025
