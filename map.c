#include "map.h"
#include "snake.h"

// Initialise la carte avec des murs sur les bords
void initialiser_Map(Map *map) {
    for (int i = 0; i < Hauteur_Map; i++) {
        for (int j = 0; j < Largeur_Map; j++) {
            if (i == 0 || i == Hauteur_Map - 1 || j == 0 || j == Largeur_Map - 1) {
                map->Grille[i][j] = '#'; // Mur
            } else {
                map->Grille[i][j] = ' '; // Espace vide
            }
        }
    }
}

// Vérifie si une position touche un mur
bool Collision_Mur(int x, int y) {
    return (x <= 0 || x >= Largeur_Map - 1 || y <= 0 || y >= Hauteur_Map - 1);
}

// Affiche la carte avec le serpent et le fruit
void afficher_Map(Map *map, Snake *snake, Position fruit) {
    // Copie la carte pour y placer le serpent temporairement
    char display[Hauteur_Map][Largeur_Map];
    for (int i = 0; i < Hauteur_Map; i++) {
        for (int j = 0; j < Largeur_Map; j++) {
            display[i][j] = map->Grille[i][j];
        }
    }

    // Ajoute le fruit sur la carte
    display[fruit.y][fruit.x] = 'F';

    // Ajoute le serpent sur la carte
    for (int i = snake->queue; i != snake->tete; i = (i + 1) % longeur_max) {
        display[snake->body[i].y][snake->body[i].x] = 'o'; // Corps du serpent
    }
    display[snake->body[snake->tete].y][snake->body[snake->tete].x] = 'O'; // Tête du serpent

    // Affiche la carte avec le serpent et le fruit
    for (int i = 0; i < Hauteur_Map; i++) {
        for (int j = 0; j < Largeur_Map; j++) {
            printf("%c", display[i][j]);
        }
        printf("\n");
    }
}
