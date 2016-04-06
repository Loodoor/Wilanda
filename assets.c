#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "assets.h"
#include "constantes.h"

void loadTiles(SDL_Surface* blocs[])
{
    blocs[VIDE] = SDL_LoadBMP("assets/Tiles/air.bmp");
    blocs[DIRT] = SDL_LoadBMP("assets/Tiles/sand_bloc.bmp");
    blocs[COIN_BLOC] = SDL_LoadBMP("assets/Tiles/coin_bloc.bmp");
    blocs[GRASS] = SDL_LoadBMP("assets/Tiles/grass_bloc.bmp");
    blocs[LAVA] = SDL_LoadBMP("assets/Tiles/lava_bloc.bmp");
    blocs[WATER] = SDL_LoadBMP("assets/Tiles/water_bloc.bmp");
    blocs[STONE] = SDL_LoadBMP("assets/Tiles/stone_bloc.bmp");
}

void loadPersoImages(SDL_Surface* persos[][2])
{
    persos[0][GAUCHE] = SDL_LoadBMP("assets/Personnage/LEFT/normal.bmp");
    persos[1][GAUCHE] = SDL_LoadBMP("assets/Personnage/LEFT/start.bmp");
    persos[2][GAUCHE] = SDL_LoadBMP("assets/Personnage/LEFT/middle.bmp");
    persos[3][GAUCHE] = SDL_LoadBMP("assets/Personnage/LEFT/end.bmp");
    persos[0][DROITE] = SDL_LoadBMP("assets/Personnage/RIGHT/normal.bmp");
    persos[1][DROITE] = SDL_LoadBMP("assets/Personnage/RIGHT/start.bmp");
    persos[2][DROITE] = SDL_LoadBMP("assets/Personnage/RIGHT/middle.bmp");
    persos[3][DROITE] = SDL_LoadBMP("assets/Personnage/RIGHT/end.bmp");
}
