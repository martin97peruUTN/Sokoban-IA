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
#include "Case.h"
#include "Coup.h"

#include <vector>

using namespace std;
#ifndef IHMSOKOBAN_T
#define IHMSOKOBAN_T
class JeuSokoban{
public:
  JeuSokoban();
  /**
   * permet de modifier le jeu en jouant un coup
   * @param p le coup à jouer
   */
  void joueurCoup(Coup p);
  /**
   * Recupère le nombre total de caisses dans le niveau
   */
  int getNbCaisse();
  /**
   * recupere le nombre de caisses actuellement bien placés dans le niveau
   */
  int getNbCaisseBienPlacees();
  /**Permet de lire le niveau dans un fichiers
   */
  void initialiserFichier();
  
  Case getCase(int i,int j);
  
  int getLargeur();
  
  int getHauteur();
  
  int getXperso();
  
  int getYperso();
  
  int getNbCaisseGrille();
  
  int getXiemeCaisse(int i);
  
  int getYiemeCaisse(int i);
private:
  vector<vector<Case> > terain;
  vector<int> listeXCaisse,listeYCaisse;
  int xJoueur,yJoueur;
  int nbCaisseBienPlacees;
  int nbCaisseGrille;
  int nbCaisse;
};
#endif 
