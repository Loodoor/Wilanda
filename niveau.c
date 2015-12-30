#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "niveau.h"
#include "constantes.h"

char blocs_jeu[6] = {0, 1, 1, 1, 0, 0};

void creerNiveau(char niveau[][MAP_HEIGHT])
{
    for(int i=0; i < MAP_WIDTH; i++)
    {
        for(int j=0; j < MAP_HEIGHT; j++)
        {
            niveau[i][j] = VIDE;
            if(j == MAP_HEIGHT - 4)
                niveau[i][j] = GRASS;
            if (j >= MAP_HEIGHT - 3)
                niveau[i][j] = DIRT;
            if(j == 0 && i % 5 == 0)
                niveau[i][j] = LAVA;
        }
    }
    /// on enregistre la carte !
    char caractere = "0";
    FILE* ecrire_carte = NULL;
    ecrire_carte = fopen("assets/Maps/map.txt", "w");
    for(int k=0; k < MAP_WIDTH; k++)
    {
        for(int l=0; l < MAP_HEIGHT; l++)
        {
            fprintf(ecrire_carte, "%d", niveau[k][l]);
        }
    }
}

void chargerNiveau(char *niveau[][MAP_HEIGHT])
{
    FILE* fichier = NULL;
    char ligneFichier[MAP_WIDTH * MAP_HEIGHT + 1] = {""};

    fichier = fopen("assests/Maps/map.txt", "r");
    if (fichier == NULL)
        return 0;

    /// lecture du fichier
    fgets(ligneFichier, MAP_WIDTH * MAP_HEIGHT + 1, fichier);

    /// création de la carte
    for(int i=0; i < MAP_WIDTH; i++)
    {
        for(int j=0; j < MAP_HEIGHT; j++)
        {
            switch(ligneFichier[(i * MAP_WIDTH) + j])
            {
                case '0':
                    niveau[i][j] = VIDE;
                    break;

                case '1':
                    niveau[i][j] = DIRT;
                    break;

                case '2':
                    niveau[i][j] = COIN_BLOC;
                    break;

                case '3':
                    niveau[i][j] = GRASS;
                    break;

                case '4':
                    niveau[i][j] = LAVA;
                    break;

                case '5':
                    niveau[i][j] = WATER;
                    break;
            }
        }
    }
    fclose(fichier);
}

void afficherNiveau(SDL_Surface *ecran, char niveau[][MAP_HEIGHT], SDL_Surface *blocs[6])
{
    SDL_Rect position;
    for(int i=0; i < MAP_WIDTH; i++)
    {
        for(int j=0; j < MAP_HEIGHT; j++)
        {
            position.x = i * TILE_SIZE;
            position.y = j * TILE_SIZE;
            SDL_BlitSurface(blocs[niveau[i][j]], NULL, ecran, &position);
        }
    }
}

void deplacement(int direction, SDL_Rect *position, char niveau[][MAP_HEIGHT])
{
    int case_x = position->x / TILE_SIZE;
    int case_y = position->y / TILE_SIZE;
    switch(direction)
    {
        case GAUCHE:
            if(case_x - 1 >= 0 && blocs_jeu[niveau[case_x - 1][case_y]] == 0 && blocs_jeu[niveau[case_x - 1][case_y + 1]] == 0)
                position->x--;
            break;

        case DROITE:
            if(case_x + 1 <= MAP_WIDTH && blocs_jeu[niveau[case_x + 1][case_y]] == 0 && blocs_jeu[niveau[case_x - 1][case_y + 1]] == 0)
                position->x++;
            break;

        case HAUT:
            if(case_y - 1 >= 0 && blocs_jeu[niveau[case_x][case_y - 1]] == 0)
                position->y--;
            break;
    }
}

void poser_bloc(int x_souris, int y_souris, char niveau[][MAP_HEIGHT], short bloc_courant)
{
    int case_x = x_souris / TILE_SIZE;
    int case_y = y_souris / TILE_SIZE;
    if((niveau[case_x][case_y] == VIDE && bloc_courant != VIDE) || (niveau[case_x][case_y] != VIDE && bloc_courant == VIDE))
    {
        niveau[case_x][case_y] = bloc_courant;
    }
}

void gravity_fall(SDL_Rect *position, char niveau[][MAP_HEIGHT])
{
    int case_x = position->x / TILE_SIZE;
    int case_y = position->y / TILE_SIZE;
    if (niveau[case_x][case_y + 2] == VIDE)
        position->y += TILE_SIZE;
}
