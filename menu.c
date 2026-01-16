#include "menu.h"

bool showMenu(SDL_Renderer *renderer, MenuChoice *choice) {
    if (TTF_Init() == -1) {
        printf("Erreur TTF_Init: %s\n", TTF_GetError());
        return false;
    }

    TTF_Font *font = TTF_OpenFont("arial.ttf", 24); // Assure-toi que arial.ttf est dispo
    if (!font) {
        printf("Erreur chargement police: %s\n", TTF_GetError());
        return false;
    }

    SDL_Color white = {255, 255, 255};
    SDL_Event event;
    bool running = true;

    while (running) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Titre
        SDL_Surface *titleSurface = TTF_RenderText_Solid(font, "Bienvenue dans Snake !", white);
        SDL_Texture *titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
        SDL_Rect titleRect = {80, 50, titleSurface->w, titleSurface->h};
        SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
        SDL_FreeSurface(titleSurface);

        // Slogan
        SDL_Surface *sloganSurface = TTF_RenderText_Solid(font, "Prépare-toi à devenir le maître du serpent affamé !", white);
        SDL_Texture *sloganTexture = SDL_CreateTextureFromSurface(renderer, sloganSurface);
        SDL_Rect sloganRect = {40, 100, sloganSurface->w, sloganSurface->h};
        SDL_RenderCopy(renderer, sloganTexture, NULL, &sloganRect);
        SDL_FreeSurface(sloganSurface);

        // Boutons
        const char *labels[3] = {"Start", "Help", "Quit Game"};
        SDL_Rect buttons[3];

        for (int i = 0; i < 3; i++) {
            SDL_Surface *btnSurface = TTF_RenderText_Solid(font, labels[i], white);
            SDL_Texture *btnTexture = SDL_CreateTextureFromSurface(renderer, btnSurface);
            buttons[i].x = 120;
            buttons[i].y = 160 + i * 50;
            buttons[i].w = btnSurface->w;
            buttons[i].h = btnSurface->h;
            SDL_RenderCopy(renderer, btnTexture, NULL, &buttons[i]);
            SDL_FreeSurface(btnSurface);
        }

        SDL_RenderPresent(renderer);

        // Gestion clic
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                *choice = MENU_QUIT;
                running = false;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;
                for (int i = 0; i < 3; i++) {
                    if (x >= buttons[i].x && x <= buttons[i].x + buttons[i].w &&
                        y >= buttons[i].y && y <= buttons[i].y + buttons[i].h) {
                        *choice = i + 1; // MENU_START, MENU_HELP, MENU_QUIT
                        running = false;
                    }
                }
            }
        }
    }

    TTF_CloseFont(font);
    TTF_Quit();
    return true;
}
