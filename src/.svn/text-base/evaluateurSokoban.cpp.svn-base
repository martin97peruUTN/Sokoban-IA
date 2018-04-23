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
#include "evaluateurSokoban.h"
#include "SolutionSokoban.h"

EvaluateurSokoban::EvaluateurSokoban(JeuSokoban* j)
{
  lejeu=j;
}

std::vector< double > EvaluateurSokoban::evaluer(vector< SolutionSokoban > solutions)
{
    vector<double> res;
    
    int oldx,oldy;
    for (int i=0;i<solutions.size();i++)
    {JeuSokoban temp=*lejeu;
    int malus=0;
     oldx=temp.getXperso(); oldy=temp.getYperso();
      for (int j=0;j<solutions[i].getNbCoup();j++)
      {
	temp.joueurCoup(solutions[i].getCoup(j));
	if (oldx==temp.getXperso() and oldy==temp.getYperso())
	  malus++;
	     oldx=temp.getXperso(); oldy=temp.getYperso();
      }
      res.push_back(-10*temp.getNbCaisseBienPlacees()+0.1*solutions[i].getNbCoup()+0.3*malus+30*temp.getNbCaisseGrille());
    }
    return res;
}
