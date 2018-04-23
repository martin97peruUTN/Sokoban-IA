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
#ifndef CRITERE_ARRET_NOMBRE_ITERATION_H
#define CRITERE_ARRET_NOMBRE_ITERATION_H

#include<vector>
#include "CritereArretGenetique.h"

class CritereArretNombreIteration:public CritereArretGenetique{
private:
  int nombreIteration;
  bool quiet;
  
public:
 /**Constructeur en précisant le nombre d'itérations.
  * @param n le nombre d'itérations souhaités
  */
  CritereArretNombreIteration(int n=0);
  
   /**Constructeur en précisant le nombre d'itérations.
  * @param n le nombre d'itérations souhaités
  */
  CritereArretNombreIteration(int n,bool quiet);
  /**récupére le nombre d'itération restantes
   */
  int getNombreIteration();
  /**Permet de modifier le nombre d'itération restantes
   * @param n le nombre d'itérations souhaités 
   */
  void setNombreIteration(int n);
  /**revois vrai si on doit s'arreter
   */
  bool termine(vector<double> &scores); 
  
};
#endif