/*
  Copyright (c) 2012 Maxime Chautru
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
#include"CritereArretNombreIteration.h"
#include <iostream>
#include <algorithm>
#include "SDL/SDL.h"

using namespace std;

CritereArretNombreIteration::CritereArretNombreIteration(int n){
  nombreIteration=n; quiet=false;
}

int CritereArretNombreIteration::getNombreIteration(){
  return nombreIteration;
}

CritereArretNombreIteration::CritereArretNombreIteration(int n, bool q)
{
quiet=q;nombreIteration=n;
}

void CritereArretNombreIteration::setNombreIteration (int n)
{
  nombreIteration=n;
}

bool CritereArretNombreIteration::termine(vector<double> &scores){
  nombreIteration--;
  if (nombreIteration%5==0)
  if (!quiet)
    cout<<"Iteration "<<nombreIteration<<" score:"<<*min_element(scores.begin(),scores.end())<<" taille pop: "<<scores.size()<<endl;
  SDL_Event event;
 while( SDL_PollEvent(&event))
  if (event.type==SDL_KEYDOWN and event.key.keysym.sym==SDLK_ESCAPE)
    return 1;
  return nombreIteration<=0;
}
