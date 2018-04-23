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
#include "evaluateurSokobanPousse.h"
#include "SolutionSokobanPousse.h"
#include <cmath>

EvaluateurSokobanPousse::EvaluateurSokobanPousse()
{
}

vector< double > EvaluateurSokobanPousse::evaluer(std::vector< SolutionSokobanPousse > &solutions)
{
    vector<double> res;
    JeuSokoban jeufinal;
    int oldx,oldy;

    for (int i=0;i<solutions.size();i++)
    {
      int nbCaisseBienPlacee=0, nbCaissesGrille, longeur,mauvais, distanceCible;
      solutions[i].evaluation(nbCaisseBienPlacee, nbCaissesGrille,longeur,mauvais,distanceCible,jeufinal);
      res.push_back(-15*nbCaisseBienPlacee+distanceCible+0.35*sqrt(longeur)+0.1*solutions[i].getNbPoussee()+0.15*mauvais+30*nbCaissesGrille);
    }
    return res;
}
