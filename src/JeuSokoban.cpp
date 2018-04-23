/*
  Copyright (c) 2012 Pierre Parent, Maxime Chautru
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
#include <iostream>
#include <cstdio>

using namespace std;

JeuSokoban::JeuSokoban ()
{
nbCaisseGrille=0;
}

int
JeuSokoban::getNbCaisse ()
{
  return nbCaisse;
}

int
JeuSokoban::getNbCaisseBienPlacees ()
{
  return nbCaisseBienPlacees;
}

void
JeuSokoban::joueurCoup (Coup p)
{
  int xnewpos, ynewpos;
  xnewpos = xJoueur;
  ynewpos = yJoueur;
  int xcaissenewpos=xJoueur;
  int ycaissenewpos=yJoueur;
  
  if (p == gauche){
    xnewpos--;
    xcaissenewpos-=2;
  }
  if (p == droite){
    xcaissenewpos+=2;
    xnewpos++;
  }
  if (p == haut){
    ynewpos--;
    ycaissenewpos-=2;
  }
  if (p == bas){
    ynewpos++;
    ycaissenewpos+=2;
  }

  if (xnewpos >= 0 and xnewpos < terain[0].size ()and ynewpos >=
      0 and ynewpos < terain.size ()) {
    switch (terain[ynewpos][xnewpos]) {
    case rien:
      xJoueur = xnewpos;
      yJoueur = ynewpos;
      break;
    case cible:
      xJoueur = xnewpos;
      yJoueur = ynewpos;
      break;
    case mur:
      break;
    case caisse:
      if(ycaissenewpos>=0 && ycaissenewpos<getHauteur()
	&& xcaissenewpos>=0 && ycaissenewpos<getLargeur()){
	switch(terain[ycaissenewpos][xcaissenewpos]){
	  case rien:
	    terain[ynewpos][xnewpos] = rien;
	    terain[ycaissenewpos][xcaissenewpos]=caisse;
	    xJoueur = xnewpos;
	    yJoueur = ynewpos;
	    if ( (terain[ycaissenewpos-1][xcaissenewpos]==mur and terain[ycaissenewpos][xcaissenewpos+1]==mur)
	      or (terain[ycaissenewpos][xcaissenewpos+1]==mur and terain[ycaissenewpos+1][xcaissenewpos]==mur)
	      or (terain[ycaissenewpos+1][xcaissenewpos]==mur and terain[ycaissenewpos][xcaissenewpos-1]==mur)
	      or (terain[ycaissenewpos][xcaissenewpos-1]==mur and terain[ycaissenewpos-1][xcaissenewpos]==mur))
	      nbCaisseGrille++;
	    for (int i=0;i<listeXCaisse.size();i++)
	      if (listeXCaisse[i]==xnewpos and listeYCaisse[i]==ynewpos)
		{listeXCaisse[i]=xcaissenewpos;listeYCaisse[i]=ycaissenewpos;}
	    break;
	  case cible:
	    terain[ynewpos][xnewpos] = rien;
	    terain[ycaissenewpos][xcaissenewpos]=caisseEtCible;
	    xJoueur = xnewpos;
	    yJoueur = ynewpos;
	    nbCaisseBienPlacees++;
	    for (int i=0;i<listeXCaisse.size();i++)
	      if (listeXCaisse[i]==xnewpos and listeYCaisse[i]==ynewpos)
		{listeXCaisse[i]=xcaissenewpos;listeYCaisse[i]=ycaissenewpos;}
	    break;
	}
      } break;
    case caisseEtCible:
      if(ycaissenewpos>=0 && ycaissenewpos<getHauteur()
	&& xcaissenewpos>=0 && ycaissenewpos<getLargeur()){
	switch(terain[ycaissenewpos][xcaissenewpos]){
	  case rien:
	    terain[ynewpos][xnewpos] = cible;
	    terain[ycaissenewpos][xcaissenewpos]=caisse;
	    xJoueur = xnewpos;
	    yJoueur = ynewpos;
	    nbCaisseBienPlacees--;
	   if ( (terain[ycaissenewpos-1][xcaissenewpos]==mur and terain[ycaissenewpos][xcaissenewpos+1]==mur)
	      or (terain[ycaissenewpos][xcaissenewpos+1]==mur and terain[ycaissenewpos+1][xcaissenewpos]==mur)
	      or (terain[ycaissenewpos+1][xcaissenewpos]==mur and terain[ycaissenewpos][xcaissenewpos-1]==mur)
	      or (terain[ycaissenewpos][xcaissenewpos-1]==mur and terain[ycaissenewpos-1][xcaissenewpos]==mur))
	      nbCaisseGrille++;
	   
	   for (int i=0;i<listeXCaisse.size();i++)
	      if (listeXCaisse[i]==xnewpos and listeYCaisse[i]==ynewpos)
		{listeXCaisse[i]=xcaissenewpos;listeYCaisse[i]=ycaissenewpos;}
	   break;
	  case cible:
	    terain[ynewpos][xnewpos] = cible;
	    terain[ycaissenewpos][xcaissenewpos]=caisseEtCible;
	    xJoueur = xnewpos;
	    yJoueur = ynewpos;
	    for (int i=0;i<listeXCaisse.size();i++)
	      if (listeXCaisse[i]==xnewpos and listeYCaisse[i]==ynewpos)
		{listeXCaisse[i]=xcaissenewpos;listeYCaisse[i]=ycaissenewpos;}
	    break;
	}
      }
    }
  }
}

void JeuSokoban::initialiserFichier ()
{
  int n, m;
  nbCaisse = 0;
  nbCaisseBienPlacees = 0;
  nbCaisseGrille=0;
  cin >> n;
  cin >> m;

  for (int i = 0; i < n; i++) {
    vector < Case > temp;
    char temp2;
    temp.clear ();
    for (int j = 0; j < m; j++) {
      scanf ("%c", &temp2);
      switch (temp2) {
      case ' ':
	temp.push_back (rien);
	break;
      case '*':
	temp.push_back (mur);
	break;
      case 'x':
	temp.push_back (caisse);
	nbCaisse++;listeXCaisse.push_back(j);listeYCaisse.push_back(i);
	break;
      case 'O':
	temp.push_back (cible);
	break;
      case '0':
	temp.push_back (caisseEtCible);
	nbCaisseBienPlacees++;
	nbCaisse++;listeXCaisse.push_back(j);listeYCaisse.push_back(i);
	break;
      case '\n':
	j--;
	break;
      }

    }
    terain.push_back (temp);
  }
  cin >> xJoueur;
  cin >> yJoueur;
}

Case JeuSokoban::getCase (int i, int j)
{
  return terain[i][j];
}

int
JeuSokoban::getHauteur ()
{
  return terain.size ();
}

int
JeuSokoban::getLargeur ()
{
  return terain[0].size ();
}

int
JeuSokoban::getXperso ()
{
  return xJoueur;
}

int
JeuSokoban::getYperso ()
{
  return yJoueur;
}

int JeuSokoban::getNbCaisseGrille()
{
return nbCaisseGrille;
}

int JeuSokoban::getXiemeCaisse(int i)
{
return listeXCaisse[i];
}

int JeuSokoban::getYiemeCaisse(int i)
{
return listeYCaisse[i];
}

