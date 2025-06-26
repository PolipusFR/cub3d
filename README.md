# Cub3D - A Raycasting Project

![Cub3D Screenshot](screenshot.png) <!-- Ajoutez une capture d'écran plus tard -->

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
- MiniLibX (incluse ou système)

## Installation

1. Clonez le dépôt :
```bash
git clone https://github.com/PolipusFR/cub3d
cd cub3d
