#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "constantes.h"
#include "niveau.h"
#include "assets.h"
#include "jeu.h"

void jouer(SDL_Surface *ecran)
{
    /// variables
    /// SDL
    fprintf(stdout, "Creation des surfaces et des rect\n");
    SDL_Event event;
    SDL_Surface *persos[4][2];
    SDL_Surface *blocs[7];
    SDL_Surface *perso_actuel;
    SDL_Rect position_perso;
    SDL_Rect position_relative;
    position_perso.x = 0;
    position_perso.y = 0;

    fprintf(stdout, "Chargement du personnage\n");
    loadPersoImages(&persos);

    fprintf(stdout, "Chargement des tiles\n");
    loadTiles(&blocs);

    perso_actuel = persos[0][DROITE];

    /// C89
    fprintf(stdout, "Creation des variables de jeu\n");
    int continuer = 1;
    short bloc_courant = VIDE;
    char se_deplace = FALSE;
    char jump = FALSE;
    char direction = DROITE;
    short state_deplacement = 0;
    char niveau[MAP_WIDTH][MAP_HEIGHT] = {0};

    /// on regarde si on doit créer une carte ou pas
    FILE* lire_carte = NULL;
    lire_carte = fopen("assests/Maps/map.txt", "r");
    if (lire_carte == NULL)
    {
        fprintf(stdout, "Creation du niveau\n");
        creerNiveau(niveau);
    }
    else
    {
        fprintf(stdout, "Lecture de la carte\n");
        fclose(lire_carte);
        chargerNiveau(niveau);
    }

    /// boucle
    while (continuer)
    {
        /// gestion des événements
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                /// on a fait la croix, on quitte
                continuer = 0;
                break;

            case SDL_MOUSEBUTTONUP:
                /// gestion du clic
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    fprintf(stdout, "Pose un bloc\n");
                    poser_bloc(event.button.x, event.button.y, niveau, bloc_courant);
                }
                break;

            case SDL_KEYDOWN:
                /// gestions des touches
                switch(event.key.keysym.sym)
                {
                    case SDLK_RIGHT:
                        deplacement(DROITE, &position_perso, niveau);
                        direction = DROITE;
                        se_deplace = TRUE;
                        state_deplacement += 1;
                        break;

                    case SDLK_LEFT:
                        deplacement(GAUCHE, &position_perso, niveau);
                        direction = GAUCHE;
                        se_deplace = TRUE;
                        state_deplacement += 1;
                        break;

                    case SDLK_SPACE:
                        if(!jump)
                            position_relative.y = (-0.04 * (position_relative.x * position_relative.x));
                        se_deplace = TRUE;
                        jump = TRUE;
                        break;

                    default:
                        break;
                }
                break;

                case SDL_KEYUP:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_RIGHT:
                            se_deplace = FALSE;
                            state_deplacement = 0;
                            break;

                        case SDLK_LEFT:
                            se_deplace = FALSE;
                            state_deplacement = 0;
                            break;

                        case SDLK_SPACE:
                            se_deplace = FALSE;
                            break;

                        case SDLK_0:
                        case SDLK_KP0:
                            bloc_courant = VIDE;
                            fprintf(stdout, "Prend du vide\n");
                            break;

                        case SDLK_1:
                        case SDLK_KP1:
                            bloc_courant = DIRT;
                            fprintf(stdout, "Prend de la terre\n");
                            break;

                        case SDLK_2:
                        case SDLK_KP2:
                            bloc_courant = COIN_BLOC;
                            fprintf(stdout, "Prend un coin bloc\n");
                            break;

                        case SDLK_3:
                        case SDLK_KP3:
                            bloc_courant = GRASS;
                            fprintf(stdout, "Prend de l'herbe\n");
                            break;

                        case SDLK_4:
                        case SDLK_KP4:
                            bloc_courant = LAVA;
                            fprintf(stdout, "Prend de la lave\n");
                            break;

                        case SDLK_5:
                        case SDLK_KP5:
                            bloc_courant = WATER;
                            fprintf(stdout, "Prend de l'eau\n");
                            break;

                        case SDLK_6:
                        case SDLK_KP6:
                            bloc_courant = STONE;
                            fprintf(stdout, "Prend de la pierre\n");
                            break;

                        default:
                            break;
                    }
                    break;

                default:
                    break;
        } /// fin de la gestion événements

        if(jump == FALSE)
        {
            /// gravité active sur le personnage
            gravity_fall(&position_perso, niveau);
            position_relative.y = 0;
        }
        else if(jump == TRUE)
        {
            /// saut du personnage
            position_relative.y = (-0.04 * (position_relative.x * position_relative.x));
            position_perso.y = position_perso.y - position_relative.y;
            if(position_relative.y == 0)
                jump = FALSE;
        }

        /// affichage de la carte
        afficherNiveau(ecran, niveau, &blocs);

        /// affichage du personnage
        if(se_deplace == TRUE)
        {
            char indice_image = state_deplacement % 3 + 2;
            perso_actuel = persos[indice_image][direction];
        }
        else
        {
            perso_actuel = persos[0][direction];
        }
        SDL_BlitSurface(perso_actuel, NULL, ecran, &position_perso);

        /// actualisation de l'écran
        SDL_Flip(ecran);
    }

    fprintf(stdout, "Sauvegarde de la carte\n");
    sauvegarderNiveau(niveau);

    fprintf(stdout, "FreeSurface\n");
    /// on free toutes les surfaces
    for (int i=0; i < 2; i++)
    {
        SDL_FreeSurface(persos[i]);
    }
    for (int i=0; i < 6; i++)
    {
        SDL_FreeSurface(blocs[i]);
    }
}
