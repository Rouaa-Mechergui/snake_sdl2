#include "graphics.h"

// Initialisation de SDL2 et création de la fenêtre
bool initGraphics(Graphics *gfx) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur SDL: %s\n", SDL_GetError());
        return false;
    }

    gfx->window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   Largeur_Map * taille_cellule, MAP_HEIGHT * taille_cellule, SDL_WINDOW_SHOWN);
    if (!gfx->window) {
        printf("Erreur création fenêtre: %s\n", SDL_GetError());
        return false;
    }

    gfx->renderer = SDL_CreateRenderer(gfx->window, -1, SDL_RENDERER_ACCELERATED);
    if (!gfx->renderer) {
        printf("Erreur création renderer: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

// Nettoyage des ressources SDL
void cleanupGraphics(Graphics *gfx) {
    SDL_DestroyRenderer(gfx->renderer);
    SDL_DestroyWindow(gfx->window);
    SDL_Quit();
}

// Dessine le jeu dans la fenêtre
void renderGame(Graphics *gfx, GameState *game) {
    // Nettoyage de l'écran (fond noir)
    SDL_SetRenderDrawColor(gfx->renderer, 0, 0, 0, 255);
    SDL_RenderClear(gfx->renderer);

    // Dessiner les murs en blanc
    SDL_SetRenderDrawColor(gfx->renderer, 255, 255, 255, 255);
    for (int i = 0; i < Largeur_Map; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            if (Collision_Mur(i, j)) {
                SDL_Rect wall = { i * taille_cellule, j * taille_cellule, taille_cellule, taille_cellule };
                SDL_RenderFillRect(gfx->renderer, &wall);
            }
        }
    }

    // Dessiner le fruit en rouge
    SDL_SetRenderDrawColor(gfx->renderer, 255, 0, 0, 255);
    SDL_Rect fruit = { game->fruit.x * taille_cellule, game->fruit.y * taille_cellule, taille_cellule, taille_cellule };
    SDL_RenderFillRect(gfx->renderer, &fruit);

    // Dessiner le serpent en vert
    SDL_SetRenderDrawColor(gfx->renderer, 0, 255, 0, 255);
    for (int i = game->snake.queue; i != game->snake.tete; i = (i + 1) % longeur_max) {
        SDL_Rect bodyPart = { game->snake.body[i].x * taille_cellule, game->snake.body[i].y * taille_cellule, taille_cellule, taille_cellule };
        SDL_RenderFillRect(gfx->renderer, &bodyPart);
    }

    // Dessiner la tête du serpent en bleu
    SDL_SetRenderDrawColor(gfx->renderer, 0, 0, 255, 255);
    SDL_Rect head = { game->snake.body[game->snake.tete].x * taille_cellule, game->snake.body[game->snake.tete].y * taille_cellule, taille_cellule, taille_cellule };
    SDL_RenderFillRect(gfx->renderer, &head);

    // Mettre à jour l'affichage
    SDL_RenderPresent(gfx->renderer);
}

