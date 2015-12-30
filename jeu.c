#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "constantes.h"
#include "niveau.h"
#include "jeu.h"

void jouer(SDL_Surface *ecran)
{
    /// variables
    /// SDL
    SDL_Event event;
    SDL_Surface *persos[4][2];
    SDL_Surface *blocs[6];
    SDL_Surface *perso_actuel;
    SDL_Rect position_perso;
    SDL_Rect position_relative;
    position_perso.x = 0;
    position_perso.y = 0;
    persos[0][GAUCHE] = SDL_LoadBMP("assets/Personnage/LEFT/normal.bmp");
    persos[1][GAUCHE] = SDL_LoadBMP("assets/Personnage/LEFT/start.bmp");
    persos[2][GAUCHE] = SDL_LoadBMP("assets/Personnage/LEFT/middle.bmp");
    persos[3][GAUCHE] = SDL_LoadBMP("assets/Personnage/LEFT/end.bmp");
    persos[0][DROITE] = SDL_LoadBMP("assets/Personnage/RIGHT/normal.bmp");
    persos[1][DROITE] = SDL_LoadBMP("assets/Personnage/RIGHT/start.bmp");
    persos[2][DROITE] = SDL_LoadBMP("assets/Personnage/RIGHT/middle.bmp");
    persos[3][DROITE] = SDL_LoadBMP("assets/Personnage/RIGHT/end.bmp");
    blocs[VIDE] = SDL_LoadBMP("assets/Tiles/air.bmp");
    blocs[DIRT] = SDL_LoadBMP("assets/Tiles/sand_bloc.bmp");
    blocs[COIN_BLOC] = SDL_LoadBMP("assets/Tiles/coin_bloc.bmp");
    blocs[GRASS] = SDL_LoadBMP("assets/Tiles/grass_bloc.bmp");
    blocs[LAVA] = SDL_LoadBMP("assets/Tiles/lava_bloc.bmp");
    blocs[WATER] = SDL_LoadBMP("assets/Tiles/water_bloc.bmp");
    perso_actuel = persos[0][DROITE];
    ///C89
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
        creerNiveau(niveau);
    }
    else
    {
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

            case SDL_MOUSEBUTTONDOWN:
                /// gestion du clic
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    poser_bloc(event.button.x, event.button.y, niveau, bloc_courant);
                }

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
                            position_relative.y = (-0.04 * (position_relative.x * position_relative.x) + 100);
                        se_deplace = TRUE;
                        jump = TRUE;
                        break;

                    case SDLK_0:
                        bloc_courant = VIDE;
                        break;

                    case SDLK_1:
                        bloc_courant = DIRT;
                        break;

                    case SDLK_2:
                        bloc_courant = COIN_BLOC;
                        break;

                    case SDLK_3:
                        bloc_courant = GRASS;
                        break;

                    case SDLK_4:
                        bloc_courant = LAVA;
                        break;

                    case SDLK_5:
                        bloc_courant = WATER;
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

                        default:
                            break;
                    }
                    break;

                default:
                    break;
        }
        if(jump == FALSE)
        {
            /// gravité active sur le personnage
            gravity_fall(&position_perso, niveau);
            position_relative.y = 0;
        }
        else if(jump == TRUE)
        {
            /// saut du personnage
            position_relative.y = (-0.04 * (position_relative.x * position_relative.x) + 100);
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
