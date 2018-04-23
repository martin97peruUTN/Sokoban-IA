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
#include "SolutionSokoban.h"

#ifndef SolutionSokobanPousse_H
#define SolutionSokobanPousse_H
/**@class SolutionSokobanPousse cette classe correspond à une solution de sokoban par poussées de caisses.
 * c'est à dire donnant une liste d'instruction de caisses à pousser dans une certaine directions
 * exemple:
 * pousser caisse 1 à droite, puis
 * pousser caisse 5 en haut puis
 * pousser caisse 2 en bas.
 * 
 * Il faut ensuite réaliser un plus cour chemin afin de voir comment réaliser ces opérations, et si c'est possible.
 */
class SolutionSokobanPousse{
public:
  /** Constructeur d'une solution sokoban par poussées, construite comme une suite d'instruction de 
   * poussées de caisses
   * @param lejeu un pointeur vers le jeu sur lequel s'applique cette solution
   */
  SolutionSokobanPousse(JeuSokoban *leJeu);
  /**Récupére le nombre de poussées dont est composé la solution
   */
  int getNbPoussee();
  /**Permet d'initialiser aléatoirement une solution d'un nombre fixé de poussées
   * @param nbPoussee le nombre de poussées souhaitées
   */
  void randomInit(int nbPoussee);
  /** Recupére une version mutée de la solution
   */
  SolutionSokobanPousse muter() const;
  /** Récupére un croisement entre deux solution
   */
  SolutionSokobanPousse croiser(SolutionSokobanPousse &autre) const;
  /**Convertie la solution en solutionSokoban
   */
  SolutionSokoban convertir();
  
  /** Permet de calculer certain paramettres utiles à l'évalutation
   */
  void evaluation(int &nbCaisseBienPlacee, int &nbCaissesGrille,int &longeur,int &mauvais,int &distanceCaissesCible,JeuSokoban &jeufinal) const;
  
  JeuSokoban * getJeu();
  
private:
  vector<Coup> directions;
  vector<int> caisses;
  JeuSokoban *leJeu;
};
#endif