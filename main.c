#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "constantes.h"
#include "jeu.h"

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    /// variables
    /// SDL
    SDL_Surface *ecran = NULL, *rectangle = NULL;
    SDL_Event event;
    SDL_Rect position;
    position.x = 0;
    position.y = 0;
    /// C89
    int continuer_menu = 1;

    /// l'ecran
    SDL_WM_SetIcon(SDL_LoadBMP("assets/Window/icone.bmp"), NULL);
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32,
                             SDL_HWSURFACE | SDL_DOUBLEBUF);

    /// une erreur est survenue lors du lancement du programme
    if (ecran == NULL)
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    /// sinon, tout va bien :D
    /// titre
    fprintf(stdout, "Creation de la fenetre\n");
    SDL_WM_SetCaption("Wilanda", NULL);

    /// création des surfaces
    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 220, 180, 32, 0, 0, 0, 0);

    /// coloration des surfaces
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 17, 206, 112));
    SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

    /// répétition des touches
    SDL_EnableKeyRepeat(100, 100);

    /// boucle
    while (continuer_menu)
    {
        /// gestion des événements
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                /// on a fait la croix, on quitte
                continuer_menu = 0;
                break;

            case SDL_KEYDOWN:
                /// gestions des touches
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer_menu = 0;
                        break;

                    default:
                        fprintf(stdout, "Lancement du jeu\n");
                        jouer(ecran);
                        break;
                }
                break;

                default:
                    break;
        }

        /// affichage des éléments à l'écran
        SDL_BlitSurface(rectangle, NULL, ecran, &position);

        /// actualisation de l'écran
        SDL_Flip(ecran);
    }

    /// on n'oublie pas de FreeSurface et on quitte proprement ;)
    SDL_FreeSurface(rectangle); // Libération de la surface
    SDL_Quit();

    return EXIT_SUCCESS;
}
