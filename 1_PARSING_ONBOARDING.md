# 📚 Onboarding - Système de Parsing Cub3D

## 🎯 Vue d'ensemble

Ton collègue Mehdi a implémenté un système de parsing complet pour lire et valider les fichiers de configuration `.cub` du projet Cub3D. Ce document explique tout ce qui a été fait et ce qu'il reste à faire.

---

## 📁 Architecture du Parsing

Le système de parsing est divisé en **5 fichiers** dans `src/parsing/` :

```
src/parsing/
├── parsing.c           → Point d'entrée principal
├── create_map.c        → Lecture du fichier .cub
├── fill_elements.c     → Extraction des éléments de config
├── check_char_map.c    → Validation des caractères
└── check_close.c       → Vérification de la fermeture de la map
```

---

## 🏗️ Structure de Données (t_game)

Voici la structure principale qui stocke toutes les données parsées :

```c
typedef struct s_game {
    char    **map;           // Map brute (tout le fichier ligne par ligne)
    char    **square_map;    // Map carrée normalisée (avec '2' pour les espaces)
    char    *north_wall;     // Chemin vers texture Nord (ex: "./path_to_north.xpm")
    char    *south_wall;     // Chemin vers texture Sud
    char    *east_wall;      // Chemin vers texture Est
    char    *west_wall;      // Chemin vers texture Ouest
    char    *floor;          // Couleur du sol (ex: "220,100,0")
    char    *ceiling;        // Couleur du plafond (ex: "225,30,0")

    int     count_element;   // Compteur d'éléments parsés (doit être = 6)
    int     row_map_y;       // Index où commence la map dans le tableau
    t_renderer  renderer;    // Structure de rendu (pour plus tard)
} t_game;
```

---

## 🔄 Flux d'Exécution du Parsing

Voici le déroulement complet du parsing, étape par étape :

### 1️⃣ **Point d'Entrée : `parsing()`**

```c
int parsing(t_game *game, char **av)
```

**Rôle :** Orchestrer toute la validation du fichier `.cub`

**Étapes :**

1. ✅ Initialise la structure `t_game` (tous les pointeurs à NULL)
2. ✅ Vérifie que le fichier se termine par `.cub`
3. ✅ Lit le fichier avec `create_map()`
4. ✅ Extrait les éléments de config avec `fill_elements()`
5. ✅ Valide qu'on a bien 6 éléments (NO, SO, WE, EA, F, C)
6. ✅ Vérifie les murs gauches
7. ✅ Vérifie les caractères valides
8. ✅ Vérifie les murs haut/bas
9. ✅ Crée une map carrée normalisée
10. ✅ Vérifie que la map est fermée

---

### 2️⃣ **Lecture du Fichier : `create_map()`**

**Fonction :** `char **create_map(char *file)`

**Rôle :** Lire le fichier `.cub` et le stocker ligne par ligne

**Comment ça marche :**

1. Compte le nombre de lignes du fichier
2. Alloue un tableau de chaînes (`char **`)
3. Lit chaque ligne avec `get_next_line()`
4. Retourne un tableau où chaque élément = une ligne du fichier

**Résultat :**

```c
game->map[0] = "NO ./path_to_the_north_texture\n"
game->map[1] = "SO ./path_to_the_south_texture\n"
game->map[2] = "WE ./path_to_the_west_texture\n"
game->map[3] = "EA ./path_to_the_east_texture\n"
game->map[4] = "\n"
game->map[5] = "F 220,100,0\n"
game->map[6] = "C 225,30,0\n"
game->map[7] = "\n"
game->map[8] = "         1111111111111111111111111\n"
game->map[9] = "         1000000000110000000000001\n"
// ... etc
```

---

### 3️⃣ **Extraction des Éléments : `fill_elements()`**

**Fonction :** `int fill_elements(t_game *g)`

**Rôle :** Parser les 6 éléments de configuration obligatoires

**Éléments parsés :**

- `NO` → Texture mur Nord → stocké dans `game->north_wall`
- `SO` → Texture mur Sud → stocké dans `game->south_wall`
- `WE` → Texture mur Ouest → stocké dans `game->west_wall`
- `EA` → Texture mur Est → stocké dans `game->east_wall`
- `F` → Couleur du sol (Floor) → stocké dans `game->floor`
- `C` → Couleur du plafond (Ceiling) → stocké dans `game->ceiling`

**Exemple de parsing :**

```
Ligne du fichier : "NO   ./textures/north.xpm\n"
                     ^    ^
                     |    +-- Saute les espaces
                     +------- Identifie "NO"

Résultat : game->north_wall = "./textures/north.xpm"
```

**Important :**

- Saute les lignes vides
- Saute les espaces avant et après les identifiants
- Supprime le `\n` en fin de ligne
- Incrémente `count_element` à chaque élément trouvé
- S'arrête quand il trouve une ligne commençant par `1` (début de la map)
- Stocke l'index de cette ligne dans `game->row_map_y`

---

### 4️⃣ **Validation des Caractères : `check_char_map.c`**

**3 fonctions de validation :**

#### A. `check_left_wall()`

Vérifie que chaque ligne commence par `'1'` ou `' '`

#### B. `check_char()`

Vérifie que :

- ✅ Tous les caractères sont valides : `' '`, `'1'`, `'0'`, `'N'`, `'S'`, `'E'`, `'W'`
- ✅ Il y a **exactement 1 position de départ** (N/S/E/W)

#### C. `check_top_bottom_walls()`

Vérifie que :

- ✅ La première ligne ne contient que `'1'` et `' '`
- ✅ La dernière ligne ne contient que `'1'` et `' '`

---

### 5️⃣ **Normalisation de la Map : `fill_square_map()`**

**Rôle :** Créer une version "carrée" de la map pour faciliter la vérification de fermeture

**Transformation :**

- Trouve la ligne la plus longue
- Crée un tableau 2D rectangulaire
- Remplace **tous les espaces et `\n` par `'2'`**
- Conserve les autres caractères (`'1'`, `'0'`, `'N'`, `'S'`, `'E'`, `'W'`)

**Pourquoi `'2'` ?**
Parce que `'2'` représente une "zone interdite" (vide/hors-map). Ça permet de détecter si un `'0'` ou un joueur touche cette zone → map non fermée !

**Exemple :**

**Avant (map originale) :**

```
"111\n"
"1 1\n"
"111\n"
```

**Après (square_map) :**

```
"111"
"121"  // Le ' ' devient '2'
"111"
```

---

### 6️⃣ **Vérification de Fermeture : `map_close()`**

**Fonction :** `int map_close(char **map)`

**Rôle :** Vérifier que toutes les cases accessibles (`'0'`, `'N'`, `'S'`, `'E'`, `'W'`) sont entourées de murs (`'1'`)

**Algorithme :**
Pour chaque case accessible :

```c
if (case est '0' ou 'N' ou 'S' ou 'E' ou 'W') {
    if (case_au_dessus == '2' ||
        case_en_dessous == '2' ||
        case_à_gauche == '2' ||
        case_à_droite == '2') {
        return (0);  // ❌ Map pas fermée !
    }
}
```

**Cas invalide détecté :**

```
111
1 0  <- Le '0' touche le vide (représenté par '2')
111
```

---

## 🎨 Format du Fichier .cub

Exemple de fichier valide :

```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0

         1111111111111111111111111
         1000000000110000000000001
         1011000001110000000000001
         1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N011
11110111 1110101 1011110100001
11111111 1111111 111111111111
```

---

## ⚠️ CE QUI MANQUE - Le Problème Soulevé par ton Collègue

### 🔴 **Problème : Stockage des Couleurs**

Actuellement, les couleurs du sol et du plafond sont stockées comme des **chaînes de caractères** :

```c
game->floor = "220,100,0";     // ❌ String, pas exploitable pour le rendu
game->ceiling = "225,30,0";    // ❌ String, pas exploitable pour le rendu
```

### ✅ **Solution : Parser les Couleurs RGB**

Pour le rendu graphique, il faut **convertir ces strings en valeurs RGB utilisables**.

#### Option 1 : Stocker 3 entiers séparés

Modifier la structure `t_game` :

```c
typedef struct s_game {
    // ... autres champs ...

    // Remplacer :
    // char *floor;
    // char *ceiling;

    // Par :
    int floor_r;      // Rouge (0-255)
    int floor_g;      // Vert (0-255)
    int floor_b;      // Bleu (0-255)

    int ceiling_r;    // Rouge (0-255)
    int ceiling_g;    // Vert (0-255)
    int ceiling_b;    // Bleu (0-255)
} t_game;
```

#### Option 2 : Stocker une valeur hexadécimale (recommandé pour MinilibX)

```c
typedef struct s_game {
    // ... autres champs ...

    int floor_color;      // 0x00RRGGBB (ex: 0x00DC6400 pour 220,100,0)
    int ceiling_color;    // 0x00RRGGBB (ex: 0x00E11E00 pour 225,30,0)
} t_game;
```

**Formule de conversion :**

```c
color = (R << 16) | (G << 8) | B;
```

**Exemple :**

```c
// F 220,100,0
int r = 220;  // 0xDC
int g = 100;  // 0x64
int b = 0;    // 0x00

game->floor_color = (220 << 16) | (100 << 8) | 0;
// = 0x00DC6400
```

---

## 🛠️ CE QU'IL FAUT IMPLÉMENTER

### Fonction à ajouter : `parse_color()`

```c
// Fichier : src/parsing/parse_color.c

#include "../include/cub3d.h"

// Convertit une string "R,G,B" en valeur hexadécimale
int parse_color(char *color_str)
{
    char **rgb;
    int r, g, b;
    int color;

    // Split par ','
    rgb = ft_split(color_str, ',');
    if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
        return (-1);  // Erreur de format

    // Convertir en int
    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);

    // Vérifier les limites (0-255)
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        // Free rgb
        return (-1);
    }

    // Calculer la couleur finale
    color = (r << 16) | (g << 8) | b;

    // Free rgb
    free_split(rgb);

    return (color);
}
```

### Intégration dans `parsing.c`

Après avoir rempli `game->floor` et `game->ceiling`, ajouter :

```c
// Dans parsing() après fill_elements()
game->floor_color = parse_color(game->floor);
game->ceiling_color = parse_color(game->ceiling);

if (game->floor_color == -1 || game->ceiling_color == -1)
    ft_error("Invalid color format");

// Libérer les strings temporaires
free(game->floor);
free(game->ceiling);
game->floor = NULL;
game->ceiling = NULL;
```

---

## 🎯 Résumé pour toi

### ✅ Ce qui est FAIT :

- ✅ Lecture du fichier `.cub`
- ✅ Extraction des 6 éléments (NO, SO, WE, EA, F, C)
- ✅ Validation de la map (caractères, murs, fermeture)
- ✅ Création d'une map carrée normalisée
- ✅ Les chemins des textures sont stockés et prêts à être utilisés

### ⚠️ Ce qui MANQUE :

- ❌ **Parser les couleurs RGB** (actuellement stockées en string)
- ❌ Convertir `"220,100,0"` → `0x00DC6400`
- ❌ Modifier la structure `t_game` pour stocker les couleurs en `int`
- ❌ Valider que les valeurs RGB sont entre 0 et 255

---

## 📝 Questions de ton Collègue - Réponses

### ❓ "Comment stocker les chemins d'images ?"

**Réponse :** C'est déjà bien fait ! Les chemins sont stockés dans :

- `game->north_wall`
- `game->south_wall`
- `game->east_wall`
- `game->west_wall`

Tu pourras les utiliser directement avec MinilibX :

```c
void *north_img = mlx_xpm_file_to_image(mlx, game->north_wall, &w, &h);
```

### ❓ "Il manque comment stocker les couleurs du sol"

**Réponse :** Exact ! Actuellement :

```c
game->floor = "220,100,0";  // ❌ String inutilisable
```

Il faut parser cette string et la convertir en :

```c
game->floor_color = 0x00DC6400;  // ✅ Valeur utilisable avec mlx_pixel_put()
```

---

## 🚀 Next Steps

1. **Décider du format de stockage des couleurs** (je recommande `int` avec valeur hexa)
2. **Modifier `game.h`** pour ajouter `floor_color` et `ceiling_color`
3. **Créer `parse_color.c`** avec la fonction de conversion
4. **Intégrer dans `parsing.c`**
5. **Tester avec différentes valeurs RGB**

---

## 📌 Notes Importantes

### Valeurs RGB Valides

- Chaque composante doit être entre **0 et 255**
- Format obligatoire : `R,G,B` (ex: `220,100,0`)

### Utilisation dans MinilibX

```c
// Dessiner un pixel avec la couleur du sol
mlx_pixel_put(mlx, win, x, y, game->floor_color);
```

### Gestion d'Erreurs

Le parsing vérifie déjà beaucoup de choses, mais il faudra ajouter :

- ✅ Vérifier qu'il y a exactement 3 nombres
- ✅ Vérifier que chaque nombre est entre 0 et 255
- ✅ Vérifier qu'il n'y a pas de caractères invalides

---

## 📚 Ressources Utiles

- Format hexa couleur : `0x00RRGGBB`
- Shift bitwise : `(R << 16) | (G << 8) | B`
- MinilibX doc : `man/man3/mlx_pixel_put.3`

---

## 🎓 Bon Courage !

Tu as maintenant toutes les informations pour comprendre le parsing et finir l'implémentation des couleurs ! 💪

Si tu as des questions, n'hésite pas ! 🚀
