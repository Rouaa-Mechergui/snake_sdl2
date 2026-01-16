#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "snake.h"

#define Largeur_Map 40  // Largeur de la carte
#define Hauteur_Map 25 // Hauteur de la carte (ajustée pour éviter trop de scrolling)

// Structure pour représenter la carte
typedef struct {
    char Grille[Largeur_Map][Hauteur_Map]; // Grille de la carte
} Map;

// Fonctions du module Map
void initialiser_Map(Map *map);
void afficher_Map(Map *map, Snake *snake, Position fruit);
bool Collision_Mur(int x, int y);

#endif // MAP_H

