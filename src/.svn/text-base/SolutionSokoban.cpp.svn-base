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
#include <cstdlib>

SolutionSokoban::SolutionSokoban(JeuSokoban* j)
{
	leJeu=j;
}

int SolutionSokoban::getNbCoup()
{
return coups.size();
}

Coup SolutionSokoban::getCoup(int i)
{
  return coups[i];
}

void SolutionSokoban::randomInit(int nb)
{
  coups.clear();
  Coup joker;
for (int i=0;i<nb;i++)
  {
    joker=(Coup)(rand()%4);
    int test=rand()%5;
    switch(test)
    {
      case 0:
	coups.push_back(bas);break;
      case 1:
	coups.push_back(haut);break;
      case 2:
	coups.push_back(gauche);break;
      case 3:
	coups.push_back(droite);break;
      case 4:
	coups.push_back(joker);break; 
    
    }
  }
}

SolutionSokoban SolutionSokoban::muter()
{
  SolutionSokoban res(leJeu);
  res=*this;
  int nb=rand()%10;
  for (int i=0;i<nb;i++)
  {  
    int test=rand()%3;
  if (res.coups.size()!=0)
   switch(test)
    {
      case 0:

	res.coups.erase(res.coups.begin()+rand()%res.coups.size());break;
      case 1:
	res.coups.insert(res.coups.begin()+rand()%res.coups.size(),(Coup)(rand()%4));break;
      case 2:
	res.coups[rand()%res.coups.size()]=(Coup)(rand()%4);break;
    
    }
  }
    return res;
}

SolutionSokoban SolutionSokoban::croiser(SolutionSokoban autre)
{
vector<int> pos1x,pos1y,pos2x,pos2y;
vector<int> indexEgaux1,indexEgaux2;
JeuSokoban temp=*leJeu;
int compteur=0;
int nbAleatoire;
int indexcoupe1,indexcoupe2;
SolutionSokoban res(leJeu);

for (int i=0;i<coups.size();i++)
  {
  pos1x.push_back(temp.getXperso());
  pos1y.push_back(temp.getYperso());
  temp.joueurCoup(coups[i]);
  }
  pos1x.push_back(temp.getXperso());
  pos1y.push_back(temp.getYperso());
temp=*leJeu;
for (int i=0;i<autre.getNbCoup();i++)
  {
  pos2x.push_back(temp.getXperso());
  pos2y.push_back(temp.getYperso());
  temp.joueurCoup(autre.coups[i]);
  }
  pos2x.push_back(temp.getXperso());
  pos2y.push_back(temp.getYperso());
  for (int i=0;i<pos1x.size();i++)
    for (int j=0;j<pos2x.size();j++)
    {
     if (pos1x[i]==pos2x[j] and pos1y[i]==pos2y[j])
     {
       compteur++;indexEgaux1.push_back(i);indexEgaux2.push_back(j);
     }
    }
    
  nbAleatoire=rand()%compteur;
  indexcoupe1=indexEgaux1[nbAleatoire];
  indexcoupe2=indexEgaux2[nbAleatoire];
  for (int i=0;i<indexcoupe1;i++)
    res.coups.push_back(coups[i]);
  for (int j=indexcoupe2;j<autre.getNbCoup();j++)
    res.coups.push_back(autre.coups[j]);
  return res;
}


void SolutionSokoban::ajouterCoupDebut(Coup c)
{
coups.insert(coups.begin(),c);
}


void SolutionSokoban::concatener(SolutionSokoban s)
{
for (int i=0;i<s.coups.size();i++)
  coups.push_back(s.coups[i]);
}

void SolutionSokoban::ajouterCoupFin(Coup c)
{
coups.push_back(c);
}

