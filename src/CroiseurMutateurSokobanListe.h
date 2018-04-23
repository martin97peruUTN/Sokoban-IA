/*
  Copyright (c) 2012 Maxime Chautru, Pierre Parent
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
#ifndef CROISEURMUTATEURSOKOBANLISTE_H
#define CROISEURMUTATEURSOKOBANLISTE_H

#include<vector>
#include<iostream>
#include "CroiseurMutateurSokoban.h"
#define prop_jesus_crois 0
#define prop_jesus_mut 9
#include "SelecteurElitismeLoterie.h"
#include "SolveurGenetique.h"

using namespace std;

template <class T> class CroiseurMutateurSokobanListe:public CroiseurMutateurSokoban<T>
{
private:
  int nombrePostMutation;
  int nombrePreCroisement;
public:
  
  CroiseurMutateurSokobanListe(int nombreSortieCroisement,int nombreSortieMutation,int nombrePostMutation): CroiseurMutateurSokoban<T>(nombreSortieCroisement,nombreSortieMutation){
    this->nombrePostMutation=nombrePostMutation;
  }
  
  void croiserPopulation (vector < T > &population){
   /* int tailleJesus=population[0].getNbPoussee()*2;
    int nbGeneres=nombrePreCroisement;
    T inter=population[0];
    //cout<<"avant: "<<population[0].getNbCoup();
    for(int i=0;i<nbGeneres;i++){
      inter.randomInit(tailleJesus);
      population.push_back(inter);
    }*/
    //cout<<" apres: "<<population[0].getNbCoup()<<endl;
    CroiseurMutateurSokoban<T>::croiserPopulation(population);
  }
  
  void muterPopulation (vector < T > &population){
    static int nbiteration=5;
    
    nbiteration++;

    CroiseurMutateurSokoban<T>::muterPopulation(population);
    //-----------------------------------------------
    //		Ajout d'une population secondaire toutes les 20 iteration
   //------------------------------------------------
    if (nbiteration%20==0)
    {
      
    int tailleJesus=population[0].getNbPoussee()*2;
    int nbGeneres=nombrePostMutation;
    vector<T> inter;
    T temp=population[0];
    for (int i=0;i<nbGeneres;i++)
      {
      temp.randomInit(rand()%tailleJesus);
      inter.push_back(temp);
      }
    
    int iter=50; 
    EvaluateurSokobanPousse evaluateur;
    CritereArretNombreIteration arret(iter,true);
    CroiseurMutateurSokoban<T> croiseurMutateur(0.4*nbGeneres,nbGeneres);
    SelecteurElitismeLoterie<T> selecteur(50);
    SolveurGenetique<T> solveur;
    solveur.resoudre(evaluateur, selecteur,croiseurMutateur,arret,inter);
   
     //Evalue le score
    vector <double> scores=evaluateur.evaluer(inter);
    int indMin=0;
    for(int i=1; i<scores.size(); i++){
	  if(scores[i]<scores[indMin]){
	    indMin=i;
	  }
	}
      
      for(int i=0;i<inter.size();i++){
	population.push_back(inter[i]);
      }
      cout<<"ajout population secondaire: popsize "<<nbGeneres<<" iter "<<iter<<" score "<<scores[indMin]<<endl;
    }
    
        
  }
};

#endif // CROISEURMUTATEURSOKOBANLISTE_H
