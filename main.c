#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "game.h"
#include "graphics.h"

#define delai 200  // Délai entre les frames (ms)

int main(int argc, char *argv[]) {
    GameState game;
    Graphics gfx;

    // Initialisation SDL et fenêtre
    if (!initGraphics(&gfx)) {
        printf("Erreur initialisation SDL.\n");
        return 1;
    }

    // Initialisation du jeu avec le serpent au centre
    initialiser_jeu(&game, Largeur_Map / 2, Hauteur_Map / 2, false);

    bool running = true;
    SDL_Event event;

    // Boucle de jeu principale
    while (running && !game.game_over) {
        // Gestion des événements clavier
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:    changer_direction(&game, UP); break;
                    case SDLK_DOWN:  changer_direction(&game, DOWN); break;
                    case SDLK_LEFT:  changer_direction(&game, LEFT); break;
                    case SDLK_RIGHT: changer_direction(&game, RIGHT); break;
                    case SDLK_ESCAPE: running = false; break;
                }
            }
        }

        // Mettre à jour le jeu
        update_jeu(&game);

        // Afficher le jeu
        renderGame(&gfx, &game);

        SDL_Delay(delai); // Délai pour contrôler la vitesse
    }

    // Afficher le score à la fin
    printf("\n--- GAME OVER ---\n");
    printf("Score : %d\n", game.score);

    // Nettoyage SDL
    cleanupGraphics(&gfx);
    SDL_Quit();

    return 0;
}

