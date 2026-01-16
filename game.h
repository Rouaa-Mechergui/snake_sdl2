
#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include "map.h"

#define Largeur_Map 40
#define MAP_HEIGHT 25

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef struct {
    Snake snake;
    Map map;
    Direction current_dir;
    Direction next_dir;
    Position fruit;
    int score;
    bool game_over;
    bool wrap_around; // Si true, le serpent traverse les bords
} GameState;

// Initialisation du jeu
void initialiser_jeu(GameState *game, int X0, int Y0, bool wrap_around);

// Mise à jour de l'état du jeu
void update_jeu(GameState *game);

// Changement de direction
void changer_direction(GameState *game, Direction new_dir);

// Gestion des fruits
void spawnFruit(GameState *game);

// Vérification des collisions
bool Verif_Collisions(GameState *game);

// Vérification des collisions avec les murs
//bool isWallCollision(int x, int y);

#endif // GAME_H

