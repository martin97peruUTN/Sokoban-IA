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
#include "Coup.h"
#include "JeuSokoban.h"
#include <vector>

#ifndef SOLUTIONSOKOBAN_H
#define SOLUTIONSOKOBAN_H
using namespace std;

class SolutionSokoban{
  
public:
  SolutionSokoban(JeuSokoban *leJeu);
  int getNbCoup();
  Coup getCoup(int i);
  void randomInit(int nbCoup);
  SolutionSokoban muter();
  SolutionSokoban croiser(SolutionSokoban autre);
  void afficher();
  void ajouterCoupDebut(Coup c);
  void ajouterCoupFin(Coup c);
  void concatener(SolutionSokoban s);
private:
  vector<Coup> coups; 
  JeuSokoban *leJeu;
};

#endif
