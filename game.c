#include "game.h"
#include <stdlib.h>
#include <time.h>
#include "map.h"


void initialiser_jeu(GameState *game, int X0, int Y0, bool wrap_around) {
    initialiser_Map(&game->map);
    initialiser_serpent(&game->snake, X0, Y0);
    game->current_dir = RIGHT;
    game->next_dir = RIGHT;
    game->score = 0;
    game->game_over = false;
    game->wrap_around = wrap_around;
    srand(time(NULL));
    spawnFruit(game);
}

void update_jeu(GameState *game) {
    // Appliquer la direction si valide
    if ((game->current_dir == UP && game->next_dir != DOWN) ||
        (game->current_dir == DOWN && game->next_dir != UP) ||
        (game->current_dir == LEFT && game->next_dir != RIGHT) ||
        (game->current_dir == RIGHT && game->next_dir != LEFT)) {
        game->current_dir = game->next_dir;
    }

    // Calculer la nouvelle position
    Position tete = game->snake.body[game->snake.tete];
    Position nv_tete = tete;

    switch (game->current_dir) {
        case UP:    nv_tete.y--; break;
        case DOWN:  nv_tete.y++; break;
        case LEFT:  nv_tete.x--; break;
        case RIGHT: nv_tete.x++; break;
    }

    // Gestion du wrap-around
    if (game->wrap_around) {
        if (nv_tete.x < 0) nv_tete.x = Largeur_Map - 2;
        if (nv_tete.x >= Largeur_Map - 1) nv_tete.x = 1;
        if (nv_tete.y < 0) nv_tete.y = Hauteur_Map - 2;
        if (nv_tete.y >= Hauteur_Map - 1) nv_tete.y = 1;
    }

    // Vérifier si le serpent mange un fruit
    bool grandir = (nv_tete.x == game->fruit.x && nv_tete.y == game->fruit.y);

    // Déplacer le serpent
    if (!deplacer_serpent(&game->snake, nv_tete.x, nv_tete.y, grandir)) {
        game->game_over = true;
        return;
    }

    // Gestion après déplacement
    if (grandir) {
        game->score++;
        spawnFruit(game);
    }

    // Vérifier les collisions avec les murs si pas de wrap-around
    if (!game->wrap_around && Collision_Mur(nv_tete.x, nv_tete.y)) {
        game->game_over = true;
    }
}

void changer_direction(GameState *game, Direction new_dir) {
    game->next_dir = new_dir;
}

void spawnFruit(GameState *game) {
    Position pos;
    do {
        pos.x = 1 + rand() % (Largeur_Map - 2);
        pos.y = 1 + rand() % (Hauteur_Map - 2);
    } while (detection_collision(&game->snake, pos.x, pos.y));

    game->fruit = pos;
}

bool Verif_Collisions(GameState *game) {
    Position tete = game->snake.body[game->snake.tete];

    // Collision avec soi-même (déjà gérée dans moveSnake)
    // Collision avec les murs si pas de wrap-around
    if (!game->wrap_around && Collision_Mur(tete.x, tete.y)) {
        return true;
    }

    return false;
}

// Vérifier si le serpent touche un mur
//bool isWallCollision(int x, int y) {
    //return (x == 0 || x == Largeur_Map - 1 || y == 0 || y == MAP_HEIGHT - 1);//

