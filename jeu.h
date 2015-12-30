#ifndef DEF_JEU

#define DEF_JEU

void jouer(SDL_Surface *ecran);
void afficherPersonnage(SDL_Surface *perso_actuel, SDL_Surface *ecran, SDL_Rect *position_perso,
                        char se_deplace, short state_deplacement, SDL_Surface *persos[][2], char direction);

#endif // DEF_JEU
