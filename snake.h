
#ifndef SNAKE_H
#define SNAKE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define longeur_max 100  // Longueur max du serpent

// Structure pour représenter une position sur la grille
typedef struct {
    int x;
    int y;
} Position;

// Structure du serpent (file circulaire)
typedef struct {
    Position body[longeur_max];  // Tableau des positions
    int tete;  // Indice de la tête
    int queue;  // Indice de la queue
    int taille;  // Taille actuelle
} Snake;

// Fonctions du module Snake
void initialiser_serpent(Snake *snake, int X0, int Y0);
bool deplacer_serpent(Snake *snake, int nv_X, int nv_Y, bool grandir);
bool detection_collision(Snake *snake, int x, int y);
void afficher_serpent(Snake *snake);

#endif // SNAKE_H
