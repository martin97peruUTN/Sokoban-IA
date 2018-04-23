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
#ifndef SELECTEURELITISMELOTERIE_H
#define SELECTEURELITISMELOTERIE_H

#include"SelecteurGenetique.h"
#include<stdlib.h>
#include<stdio.h>
#include <sys/times.h>
#include <iostream>
#include <sys/time.h>

using namespace std;

template<class Solution>
class SelecteurElitismeLoterie:public SelecteurGenetique<Solution>
{
private:
  int nombreElitisme;
public:
  
  SelecteurElitismeLoterie(int n){
    setNombreElitisme(n);
  }
  
  void setNombreElitisme(int n){
    if(n>=0)
      nombreElitisme=n;
    else
      nombreElitisme=0;
  }
  
  int getNombreElistisme(){
    return nombreElitisme;
  }
  
  void selectionner(vector<Solution>& population, vector<double>& scores){
    double a;
    double somme;
    double alpha;
    vector<double> adaptation;
    int indMin=0;
    double interScores;
    Solution interPop=population[0];
    int nbLoterie;
    vector<Solution> selection;

    for(int i=0;i<scores.size();i++){
      indMin=i;
      for(int j=i+1;j<scores.size();j++){
	if(scores[j]<scores[indMin]){
	  indMin=j;
	}
      }
      interPop=population[i];
      interScores=scores[i];
      population[i]=population[indMin];
      scores[i]=scores[indMin];
      population[indMin]=interPop;
      scores[indMin]=interScores;
    }
    
    for(int i=0;i<nombreElitisme;i++){
      selection.push_back(population[i]);
    }
    somme=0;
    for(int i=0;i<scores.size();i++){
      somme+=(scores[i]-(scores[scores.size()-1]+1))*(scores[i]-(scores[scores.size()-1]+1));
    }
   // a=1/(1+somme-scores.size()*scores[indMin]+scores.size());
    alpha=1.0/(somme);
    for(int i=0;i<scores.size();i++){
      adaptation.push_back(alpha*(scores[i]-(scores[scores.size()-1]+1))*(scores[i]-(scores[scores.size()-1]+1)));
    }
    for(int i=1;i<adaptation.size();i++){
      adaptation[i]+=adaptation[i-1];
    }
    nbLoterie=(int)(population.size()*0.2)-nombreElitisme;
    for(int i=0;i<nbLoterie;i++){
      double selecteur=1.0*rand()/(double)RAND_MAX;
      int j=0;
      while(adaptation[j]<selecteur){
	j++;
      }
    //  if (rand()%30==0)
    //  cout<<scores[j]<<" "<<j<<" "<<selecteur<<" "<<scores[scores.size()-1]<<endl;;
      selection.push_back(population[j]);
    }
    
    population.clear();
    population=selection;
  }
  
};

#endif // SELECTEURELITISMELOTERIE_H
