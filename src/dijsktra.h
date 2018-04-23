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
#include "JeuSokoban.h"
#include "SolutionSokoban.h"
#ifndef DIJSKTRA_H
#define DISJKTRA_H

namespace dijsktraSokoban
{
SolutionSokoban meilleurChemin(JeuSokoban &j, int xArrive,int yArrive,int &longeur);
int distanceCaisseCible(JeuSokoban &j, int xcaisse,int ycaisse);
SolutionSokoban meilleurCheminCaisseCible(JeuSokoban &j, int xcaisse,int ycaisse);
};

#endif