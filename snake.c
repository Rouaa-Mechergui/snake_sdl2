#include "snake.h"

// Fonction pour initialiser le serpent à une position donnée
void initialiser_serpent(Snake *snake, int X0, int Y0) {
    snake->tete = 0;
    snake->queue = 0;
    snake->taille = 1;
    snake->body[0].x = X0;
    snake->body[0].y = Y0;
}

// Fonction pour déplacer le serpent
bool deplacer_serpent(Snake *snake, int nv_X, int nv_Y, bool grandir) {
    // Vérifier la collision avec soi-même
    if (detection_collision(snake, nv_X, nv_Y)) {
        return false; // Collision, game over
    }

    // Ajouter une nouvelle tête
    snake->tete = (snake->tete + 1) % longeur_max;
    snake->body[snake->tete].x = nv_X;
    snake->body[snake->tete].y = nv_Y;

    if (!grandir) {
        // Supprimer la queue si le serpent ne grandit pas
        snake->queue = (snake->queue + 1) % longeur_max;
    } else {
        snake->taille++;
    }

    return true; // Mouvement réussi
}

// Vérifie si le serpent se mord lui-même
bool detection_collision(Snake *snake, int x, int y) {
    for (int i = snake->queue; i != snake->tete; i = (i + 1) % longeur_max) {
        if (snake->body[i].x == x && snake->body[i].y == y) {
            return true; // Collision détectée
        }
    }
    return false;
}

// Fonction pour afficher le serpent (debug)
void afficher_serpent(Snake *snake) {
    printf("Serpent : ");
    for (int i = snake->queue; i != snake->tete; i = (i + 1) % longeur_max) {
        printf("(%d,%d) -> ", snake->body[i].x, snake->body[i].y);
    }
    printf("(%d,%d)\n", snake->body[snake->tete].x, snake->body[snake->tete].y);
}

