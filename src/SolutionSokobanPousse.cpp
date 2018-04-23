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
#include "SolutionSokobanPousse.h"
#include "dijsktra.h"
#include <cstdlib>
#include <algorithm>
#include <iostream>

using namespace dijsktraSokoban;

SolutionSokobanPousse::SolutionSokobanPousse (JeuSokoban * j)
{
  leJeu = j;
}

int
SolutionSokobanPousse::getNbPoussee ()
{
  return directions.size ();
}

void
SolutionSokobanPousse::randomInit (int nbCoup)
{
  directions.clear();
  caisses.clear();
  Coup joker;
  int jokercaisse = 0;
  for (int i = 0; i < nbCoup; i++)
    {
      if (rand () % 3 != 0)
	jokercaisse = rand () % leJeu->getNbCaisse ();

      caisses.push_back (jokercaisse);
      joker = (Coup) (rand () % 4);
      int test = rand () % 5;
      switch (test)
	{
	case 0:
	  directions.push_back (bas);
	  break;
	case 1:
	  directions.push_back (haut);
	  break;
	case 2:
	  directions.push_back (gauche);
	  break;
	case 3:
	  directions.push_back (droite);
	  break;
	case 4:
	  directions.push_back (joker);
	  break;

	}
    }
}

SolutionSokoban
SolutionSokobanPousse::convertir ()
{
  JeuSokoban copieJeu = *leJeu;
  int destinationx, destinationy;
  SolutionSokoban res (leJeu);
  SolutionSokoban temp (leJeu);
  int distance;
  for (int i = 0; i < directions.size (); i++)
    {
      destinationx = copieJeu.getXiemeCaisse (caisses[i]);
      destinationy = copieJeu.getYiemeCaisse (caisses[i]);
      if (directions[i] == gauche)
	destinationx++;
      if (directions[i] == droite)
	destinationx--;
      if (directions[i] == haut)
	destinationy++;
      if (directions[i] == bas)
	destinationy--;
      temp = meilleurChemin (copieJeu, destinationx, destinationy, distance);
      if (distance >= 0)
	{
	  res.concatener (temp);
	  res.ajouterCoupFin (directions[i]);
	  for (int j = 0; j < temp.getNbCoup (); j++)
	    copieJeu.joueurCoup (temp.getCoup (j));
	  copieJeu.joueurCoup (directions[i]);
	}

    }
  return res;
}

void
SolutionSokobanPousse::evaluation (int &nbCaisseBienPlacee,
				   int &nbCaissesGrille, int &longeur,
				   int &mauvais, int &distanceCible,
				   JeuSokoban & jeuFinal) const 
{
  jeuFinal = *leJeu;
  int destinationx, destinationy;
  SolutionSokoban res (leJeu);
  SolutionSokoban temp (leJeu);
  int distance;

  mauvais = 0;
  longeur = 0;
  for (int i = 0; i < directions.size (); i++)
    {
      destinationx = jeuFinal.getXiemeCaisse (caisses[i]);
      destinationy = jeuFinal.getYiemeCaisse (caisses[i]);
      if (directions[i] == gauche)
	destinationx++;
      if (directions[i] == droite)
	destinationx--;
      if (directions[i] == haut)
	destinationy++;
      if (directions[i] == bas)
	destinationy--;
      temp = meilleurChemin (jeuFinal, destinationx, destinationy, distance);
      if (distance >= 0)
	{
	  longeur += distance + 1;
	  for (int j = 0; j < temp.getNbCoup (); j++)
	    jeuFinal.joueurCoup (temp.getCoup (j));
	  jeuFinal.joueurCoup (directions[i]);
	}
      else
	mauvais++;
    }
  nbCaisseBienPlacee = jeuFinal.getNbCaisseBienPlacees ();
  nbCaissesGrille = jeuFinal.getNbCaisseGrille ();
  distanceCible = 0;
  int tempInt;
  for (int i = 0; i < jeuFinal.getNbCaisse (); i++)
    {
      if (jeuFinal.
	  getCase (jeuFinal.getYiemeCaisse (i),
		   jeuFinal.getXiemeCaisse (i)) != caisseEtCible)
	{
	  tempInt =
	    distanceCaisseCible (jeuFinal, jeuFinal.getXiemeCaisse (i),
				 jeuFinal.getYiemeCaisse (i));
	  if (tempInt < 0)
	    distanceCible += 20;
	  else
	    distanceCible += tempInt;
	}
    }
}

SolutionSokobanPousse
SolutionSokobanPousse::muter () const
{
  int nbCaisseBienPlacee, nbCaissesGrille, longeur, mauvais, distancecible;
  JeuSokoban JeuFinal;
  int indiceCaisseMalPlacce = -1;
  SolutionSokobanPousse res (leJeu);
  bool peutAjouterMeilleurCheminCaisse=(bool)rand()%2;
  int  positionMutation2;
  Coup tempCoup;
  int tempCaisse;
  
  //On choisit aléatoirement une caisse mal placée à la fin de la solution
  evaluation (nbCaisseBienPlacee, nbCaissesGrille, longeur, mauvais,
	      distancecible, JeuFinal);
  for (int j = 0; j < JeuFinal.getNbCaisse (); j++)
    {
      if (JeuFinal.
	  getCase (JeuFinal.getYiemeCaisse (j),
		   JeuFinal.getXiemeCaisse (j)) == caisse)
	{
	  if (indiceCaisseMalPlacce == -1 or rand () % JeuFinal.getNbCaisse() != 0)
	    indiceCaisseMalPlacce = j;
	}
    }
 
  res.caisses=caisses;
  res.directions=directions;
  
  Coup cp = (Coup) (rand () % 4);
  //On calcule le nombre de mutation que va subir la solution selon une certaine loi
  int nbMutation = 1+ rand () % 7+(rand () % 3 == 0)*(rand()%7)   + (rand () % 4 == 0) * 2+ (rand () % 10 == 0) * 10;

  for (int i = 0; i < nbMutation; i++)
    {
      /*-------------------------------------------------
       *On ne recalcule la direction de nouvelle poussés
       *Qu'avec une chance sur 5 pour avoir 
       *une certaine presistance dans la direction
       *-------------------------------------------------*/
      if (rand () % 4 != 0)
	cp = (Coup) (rand () % 4);
      
      //On choisit au hazard le type de mutation que l'on souhaite
      int TypeMutation = rand () % 9;
      
      if (res.directions.size () != 0)
	{
	  // Calcule ou va se faire l'insertion ou la supression
	  int positionMutation = rand () % res.directions.size ();
	  
	  switch (TypeMutation)
	    {
	     /*----------------------------------------
	      * Supression de poussée
	      * ---------------------------------------*/
	    case 0:
	      res.caisses.erase (res.caisses.begin () + positionMutation);
	      res.directions.erase (res.directions.begin () + positionMutation);
	      break;
	     /*----------------------------------------
	      * Insertion de poussée (à endroit aléatoire)
	      * ---------------------------------------*/
	    case 1:
	      res.caisses.insert (res.caisses.begin () + positionMutation,
				  (rand () % leJeu->getNbCaisse ()));
	      res.directions.insert (res.directions.begin () +positionMutation, cp);
	      break;
	    /*----------------------------------------
	     * Ajout de poussée à la fin
	     * ---------------------------------------*/
	    case 2:
	      res.directions.push_back (cp);
	      res.caisses.push_back (rand () % leJeu->getNbCaisse ());
	      break;
	     /*----------------------------------------
	     * ajout à la fin de poussée pour la caisse mal placée
	     * ---------------------------------------*/
	    case 3:
	      if (indiceCaisseMalPlacce != -1)
		{
		  res.directions.push_back (cp);
		  res.caisses.push_back (indiceCaisseMalPlacce);
		}
	      break;
	    /*----------------------------------------
	     * Ajout à la fin du plus cour chemin de 
	     * la caisse mal placée ou d'un coup aléatoire
	     * selon la stratégie choisie
	     * ---------------------------------------*/
	    case 4:
	      if (indiceCaisseMalPlacce != -1)
		{
		  if (peutAjouterMeilleurCheminCaisse)
		  {
		    res.evaluation (nbCaisseBienPlacee, nbCaissesGrille, longeur, mauvais,
			distancecible, JeuFinal);
		    SolutionSokoban chemin	=meilleurCheminCaisseCible(JeuFinal,
									      JeuFinal.getXiemeCaisse(indiceCaisseMalPlacce),
									     JeuFinal.getYiemeCaisse(indiceCaisseMalPlacce));
		    for (int k=0;k<chemin.getNbCoup();k++)
		    {res.directions.push_back(chemin.getCoup(i));
		     res.caisses.push_back(indiceCaisseMalPlacce);
		    }
		      peutAjouterMeilleurCheminCaisse=false;
		  }
		  else
		  {
		   res.directions.insert (res.directions.begin () + positionMutation, cp);
		  res.caisses.insert (res.caisses.begin () + positionMutation,
				      indiceCaisseMalPlacce);
		  }
		}
	      break;
	   /*-----------------------------------------
	    * Supression de poussée V2 
	    * pour équilibrer les probas
	    * ---------------------------------------*/
	    case 5:
	      res.caisses.erase (res.caisses.begin () + positionMutation);
	      res.directions.erase (res.directions.begin () + positionMutation);
	      break;
	      
	    /*-----------------------------------------
	    * midifie la position d'un coup
	    * ---------------------------------------*/
	    case 6:
	      tempCoup=res.directions[positionMutation];
	      tempCaisse=res.caisses[positionMutation];
	      res.directions.erase(res.directions.begin()+positionMutation);
	      res.caisses.erase(res.caisses.begin()+positionMutation);
	      if (res.caisses.size()!=0)
		positionMutation2=rand()%(res.caisses.size());
	      else
		positionMutation2=0;
	      res.directions.insert(res.directions.begin()+positionMutation2,tempCoup);
	      res.caisses.insert(res.caisses.begin()+positionMutation2,tempCaisse);
	      break;
	   case 7:
	     if (indiceCaisseMalPlacce!=-1)
	     {
		if (res.getNbPoussee()<=20)
		{
	       	  res.directions.insert (res.directions.begin () + positionMutation, cp);
		  res.caisses.insert (res.caisses.begin () + positionMutation,
				      indiceCaisseMalPlacce);
		}
		else
		{
	       	  res.directions.push_back (cp);
		  res.caisses.push_back (indiceCaisseMalPlacce);
		}
	     }
	     break;
	    /*-----------------------------------------
	    * Supression de poussée V3
	    * pour équilibrer les probas
	    * ---------------------------------------*/
	    default:
	      res.caisses.erase (res.caisses.begin () + positionMutation);
	      res.directions.erase (res.directions.begin () + positionMutation);
	      break;
	    }
	}
    }
  return res;
}

SolutionSokobanPousse
SolutionSokobanPousse::croiser (SolutionSokobanPousse & autre) const
{
  SolutionSokobanPousse res (leJeu);
  res = *this;
  int postionCroisementSol1, postionCroisementSol2;
  /*----------------------------------------------
   * On calcule d'abord aléatoirement 
   * les positions de croisement
   * ---------------------------------------------*/
  if (directions.size () != 0)
    postionCroisementSol1 = rand () % directions.size ();
  else
    postionCroisementSol1 = 0;

  if (autre.directions.size () > 1)
    postionCroisementSol2 = rand () % autre.directions.size ();
  else
    postionCroisementSol2 = 0;
  
  /*----------------------------------------------
   * On ne garde que le debut de la premiere solution
   * suivie de la fin de la seconde selon les
   * poitions précedement déterminés.
   * ---------------------------------------------*/
  res.directions.erase (res.directions.begin () + postionCroisementSol1, res.directions.end ());
  res.caisses.erase (res.caisses.begin () + postionCroisementSol1, res.caisses.end ());

  res.directions.insert (res.directions.end (),
			 autre.directions.begin () + postionCroisementSol2,
			 autre.directions.end ());
  res.caisses.insert (res.caisses.end (), autre.caisses.begin () + postionCroisementSol2,
		      autre.caisses.end ());
  return res;
}

JeuSokoban* SolutionSokobanPousse::getJeu()
{
return leJeu;
}

