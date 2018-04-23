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
#ifndef CROISEUR_MUTATEUR_SOKOBAN_HPP
#define CROISEUR_MUTATEUR_SOKOBAN_HPP
#include "CroiseurMutateur.h"
#include<stdlib.h>


template<class T> class CroiseurMutateurSokoban:public CroiseurMutateur<T>{
private:
  int nombreSortieCroisement;
  int nombreSortieMutation;
public:
  
  CroiseurMutateurSokoban (int nombreSortieCroisement,int nombreSortieMutation)
  {
    this->nombreSortieCroisement=nombreSortieCroisement;
    this->nombreSortieMutation=nombreSortieMutation;
  }
  
  
  void croiserPopulation (vector < T >
  &population)
  {
    int nombreNouveauxCroises;
    int nombreParents=population.size();
    nombreNouveauxCroises=nombreSortieCroisement-nombreParents;
    for(int i=0;i<nombreNouveauxCroises;i++){
      int premierParent=rand()%nombreParents;
      int deuxiemeParent;
      do{
	deuxiemeParent=rand()%nombreParents;
      }while(deuxiemeParent==premierParent);
      population.push_back(population[premierParent].croiser(population[deuxiemeParent]));
    }
  }
  
  
  void muterPopulation (vector < T >
  &population)
  {
    int nombreNouveauxMutes;
    int nombreMutables=population.size();
    nombreNouveauxMutes=nombreSortieMutation-nombreMutables;
    for(int i=0;i<nombreNouveauxMutes;i++){
      int individuMute;
      individuMute=rand()%(nombreMutables);
      population.push_back(population[individuMute].muter());
    }
  }
};
#endif