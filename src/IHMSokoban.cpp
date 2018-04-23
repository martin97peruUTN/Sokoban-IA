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
#include "IHMSokoban.h"
#include <unistd.h>
#include "sys/time.h"
#include "Case.h"
#include <iostream>

IHMSokoban::IHMSokoban()
{
  ecran =SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
  SDL_WM_SetCaption("Sokoban", NULL); 
  img_perso=SDL_LoadBMP("img/perso.bmp");
  img_mur=SDL_LoadBMP("img/mur.bmp");
  img_rien=SDL_LoadBMP("img/rien.bmp");
  img_caisse=SDL_LoadBMP("img/caisse.bmp");
  img_cibleEtCaisse=SDL_LoadBMP("img/caisseEtCible.bmp");
  img_cible=SDL_LoadBMP("img/cible.bmp");
  SDL_SetColorKey(img_perso, SDL_SRCCOLORKEY,SDL_MapRGB(img_perso ->format, 0, 255, 0));
  SDL_SetColorKey(img_cible, SDL_SRCCOLORKEY,SDL_MapRGB(img_perso ->format, 0,
255, 0));
    SDL_SetColorKey(img_caisse, SDL_SRCCOLORKEY,SDL_MapRGB(img_perso ->format,
0, 255, 0));
        SDL_SetColorKey(img_cibleEtCaisse, SDL_SRCCOLORKEY,SDL_MapRGB(img_perso
->format,
0, 255, 0));
	        SDL_SetColorKey(img_mur,
SDL_SRCCOLORKEY,SDL_MapRGB(img_perso
->format,
0, 255, 0));
  SDL_Init(SDL_INIT_VIDEO);
}

void IHMSokoban::afficheJeu(JeuSokoban jeu, int ms)
{
 SDL_Rect pos;
 for (int i=0;i<jeu.getHauteur();i++)
    for (int j=0;j<jeu.getLargeur();j++)
    {
      Case temp;
      temp=jeu.getCase(i,j);
      pos.x=j*40;
      pos.y=i*40;
      SDL_BlitSurface(img_rien, NULL, ecran, &pos);
      switch (temp)
      {
	case mur:
	  SDL_BlitSurface(img_mur, NULL, ecran, &pos);
	  break;  
	case caisse:
	  SDL_BlitSurface(img_caisse, NULL, ecran, &pos);
	  break;  
	case cible:
	  SDL_BlitSurface(img_cible, NULL, ecran, &pos);
	  break;  
	case caisseEtCible:
	  SDL_BlitSurface(img_cibleEtCaisse, NULL, ecran, &pos);
	  break;
	default:
	  break;
      }
      
    }
    
    pos.x=jeu.getXperso()*40;pos.y=jeu.getYperso()*40;
    SDL_BlitSurface(img_perso, NULL, ecran, &pos);
    SDL_Flip(ecran);
    usleep(ms*1000);
}



void IHMSokoban::joue(JeuSokoban j)
{
  SDL_Event event;
 while (1)
{
    SDL_WaitEvent(&event);
    switch(event.type)
    {
	case SDL_QUIT:
	return; break;
	case SDL_KEYDOWN:
		  switch (event.key.keysym.sym)
		    {
		    case SDLK_LEFT:
		      j.joueurCoup(gauche);break;
		    case SDLK_RIGHT:
		       j.joueurCoup(droite);break;
		     case SDLK_UP:
		      j.joueurCoup(haut);break;
		     case SDLK_DOWN:
		      j.joueurCoup(bas);break;
		    }
            break;
    }
  afficheJeu(j,0);
  
}
}

void IHMSokoban::afficheSolution(JeuSokoban j,SolutionSokoban s)
{
  for (int i=0;i<s.getNbCoup();i++)
  {
    afficheJeu(j,350);
    j.joueurCoup(s.getCoup(i));
  }
  afficheJeu(j,350);
  sleep(2);
}

