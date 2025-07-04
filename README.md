# Cub3D - A Raycasting Project

<!-- Ajoutez une capture d'écran plus tard -->

## Description

Cub3D est un projet graphique inspiré du célèbre jeu Wolfenstein 3D, implémentant un moteur de rendu 3D utilisant la technique du raycasting. Ce projet utilise la MiniLibX pour la gestion des fenêtres et des graphiques.

## Fonctionnalités

- Affichage d'un labyrinthe 3D avec une vue subjective
- Gestion des textures pour les murs (nord, sud, est, ouest)
- Couleurs personnalisables pour le sol et le plafond
- Contrôles fluides :
  - Déplacement avec les touches W, A, S, D
  - Rotation de la caméra avec les flèches gauche/droite
  - Fermeture du programme avec ESC ou la croix de la fenêtre
- Parsing de fichiers de configuration (.cub) avec validation
- Gestion robuste des erreurs

## Prérequis

- Compilateur GCC
- Make
- MiniLibX (incluse)

## Installation

1. Clonez le dépôt :
``` bash
git clone https://github.com/PolipusFR/cub3d
cd cub3d
```

2. Compilez le projet :
``` bash
make
```

Utilisation:
``` bash
./cub3d [carte en format ".cub"]
```

Exemple de fichier .cub valide:

``` bash
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
C 225,30,0

111111
100101
101001
1100N1
111111
```
