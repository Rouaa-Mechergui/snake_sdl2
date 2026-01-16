#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include "game.h"

// Définition de la taille des cellules (chaque case de la grille)
#define taille_cellule 20

// Structure pour stocker les éléments graphiques
typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} Graphics;

// Initialisation de la fenêtre et du rendu
bool initGraphics(Graphics *gfx);

// Nettoyage des ressources SDL
void cleanupGraphics(Graphics *gfx);

// Affichage du jeu
void renderGame(Graphics *gfx, GameState *game);

#endif // GRAPHICS_H

