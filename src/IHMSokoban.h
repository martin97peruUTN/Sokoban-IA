/*
  Copyright (c) 2012 Pierre Parent
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <SDL/SDL.h>
#include "JeuSokoban.h"
#include "SolutionSokoban.h"

class IHMSokoban
{
public:
  IHMSokoban();
 void afficheJeu( JeuSokoban j,int ms);
 void joue(JeuSokoban j);
 void afficheSolution(JeuSokoban j,SolutionSokoban s);
private:
  SDL_Surface *ecran;
  SDL_Surface *img_perso;
  SDL_Surface *img_caisse;
  SDL_Surface *img_mur;
  SDL_Surface *img_cible;
  SDL_Surface *img_cibleEtCaisse;
  SDL_Surface *img_rien;
};