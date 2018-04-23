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
#ifndef CRITERE_ARRET_GENETIQUE_H
#define CRITERE_ARRET_GENETIQUE_H

#include<vector>

using namespace std;

class CritereArretGenetique{
public:
  /**Retourne vrai si l'algorithme géntique doit s'arreter
   */
  virtual bool termine(vector<double> &scores){}
};

#endif