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
#ifndef SOLVEUR_GENETIQUE_HPP
#define SOLVEUR_GENETIQUE_HPP

#include <vector>
#include "Evaluateur.h"
#include "SelecteurGenetique.h"
#include "CritereArretGenetique.h"
#include "CroiseurMutateur.h"

using namespace std;

template<class Solution> 
class SolveurGenetique{
public:
  
  virtual Solution resoudre(Evaluateur<Solution>& evaluateur, 
			    SelecteurGenetique<Solution>& selecteur,
			    CroiseurMutateur<Solution>& croiseurMutateur,
			    CritereArretGenetique& critereArret,
			    vector<Solution> &population){
    vector<double> scores;
    Solution meilleureSolution=population[0];
    int indMin;
    double meilleurScore;
    
    
    scores=evaluateur.evaluer(population);
    indMin=0;
    for(int i=1; i<scores.size(); i++){
      if(scores[i]<scores[indMin]){
	indMin=i;
      }
    }
    
    meilleurScore=scores[indMin];
    meilleureSolution=population[indMin];
    selecteur.selectionner(population,scores);
    croiseurMutateur.croiserPopulation(population);
    croiseurMutateur.muterPopulation(population);
    
    	scores=evaluateur.evaluer(population);
	indMin=0;
	for(int i=1; i<scores.size(); i++){
	  if(scores[i]<scores[indMin]){
	    indMin=i;
	  }
	}
	
    while(!critereArret.termine(scores)){

	if(scores[indMin]<meilleurScore){
	  meilleurScore=scores[indMin];
	  meilleureSolution=population[indMin];
	}
	selecteur.selectionner(population,scores);
	croiseurMutateur.croiserPopulation(population);
	croiseurMutateur.muterPopulation(population);
	
		scores=evaluateur.evaluer(population);
	indMin=0;
	for(int i=1; i<scores.size(); i++){
	  if(scores[i]<scores[indMin]){
	    indMin=i;
	  }
	}
    }
    return meilleureSolution;
  }
};
#endif