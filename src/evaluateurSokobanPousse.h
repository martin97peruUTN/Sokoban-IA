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
#include "Evaluateur.h"
#include "SolutionSokobanPousse.h"

#ifndef EVALUATEUR_SOKOBAN_POUSSE_H
#define EVALUATEUR_SOKOBAN_POUSSE_H
class EvaluateurSokobanPousse:public Evaluateur<SolutionSokobanPousse>{
  
  public:
    /**Constructeur de l'évaluatuer de solution
     * @param jeu le jeu pour lequel on évalue cette solution
     */
    EvaluateurSokobanPousse();
    /**Permet d'évaluer une population de solutions
     */
    std::vector< double > evaluer(vector< SolutionSokobanPousse > &solutions);
  private:
  
};

#endif