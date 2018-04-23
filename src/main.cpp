/*
  Copyright (c) 2012 Pierre Parent, Maxime Chatru
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
#include "IHMSokoban.h"
#include "SelecteurElitismeLoterie.h"
#include "CritereArretNombreIteration.h"
#include "CroiseurMutateurSokoban.h"
#include "evaluateurSokoban.h"
#include "SolveurGenetique.h"
#include <cstdlib>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include "dijsktra.h"
#include "SolutionSokobanPousse.h"
#include "evaluateurSokobanPousse.h"
#include "CroiseurMutateurSokobanListe.h"
#include <cstring>

#define taillePop 1300
#define nombreCoupsMax 30

using namespace std;
int main(int argc,char *argv[])
{
  srand(time(NULL));
  //srand(42);
  JeuSokoban j,j2;
  j.initialiserFichier();
  IHMSokoban i;
  SolutionSokoban s(&j);
  j2=j;
  int compteur=0;
  int nbCaisses;
  JeuSokoban jeuFinal;
  
  int nbCaisseBienPlacee=0, nbCaissesGrille, longeur,mauvais,distanceCaisseCibl;
  EvaluateurSokobanPousse evaluateur;
  CritereArretNombreIteration arret(700);
  CroiseurMutateurSokobanListe<SolutionSokobanPousse> croiseurMutateur(40,taillePop,100);
  SelecteurElitismeLoterie<SolutionSokobanPousse> selecteur(75);
  SolveurGenetique<SolutionSokobanPousse> solveur;
  SolutionSokoban meilleureSol(&j);
  
  vector<SolutionSokobanPousse> population;
  for (int i=0;i<taillePop;i++){
    SolutionSokobanPousse solution(&j);
    solution.randomInit((rand()%(nombreCoupsMax-7))+7);
    population.push_back(solution);
  }
  if (argc>1 and strcmp(argv[1],"-play")==0)
  {
  i.joue(j);
  }
  else
  {
  SolutionSokobanPousse sol(&j);
  i.afficheJeu(j,10);
  sol=solveur.resoudre(evaluateur, selecteur,croiseurMutateur,arret,population);
  sol.evaluation(nbCaisseBienPlacee, nbCaissesGrille,longeur,mauvais,distanceCaisseCibl,jeuFinal);
    
 cout<<nbCaisseBienPlacee<<" caisses bien placées"<<endl;
  i.afficheSolution(j,sol.convertir());
  }
  
}
