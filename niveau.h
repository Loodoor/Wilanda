#include "constantes.h"

#ifndef DEF_NIVEAU

#define DEF_NIVEAU

void creerNiveau(char niveau[][MAP_HEIGHT]);
void chargerNiveau(char *niveau[][MAP_HEIGHT]);
void afficherNiveau(SDL_Surface *ecran, char niveau[][MAP_HEIGHT], SDL_Surface *blocs[6]);
void deplacement(int direction, SDL_Rect *position, char niveau[][MAP_HEIGHT]);
void poser_bloc(int x_souris, int y_souris, char niveau[][MAP_HEIGHT], short bloc_courant);
void gravity_fall(SDL_Rect *position, char niveau[][MAP_HEIGHT]);

#endif // DEF_NIVEAU
