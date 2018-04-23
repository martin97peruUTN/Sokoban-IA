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
#include "dijsktra.h"
#include <iostream>

SolutionSokoban dijsktraSokoban::meilleurChemin(JeuSokoban& jeu, int xArrive, int yArrive, int& longeur)
{
int carte[1000][1000];
vector<int> listx,listy;
vector<int> listxn,listyn;
SolutionSokoban res(&jeu);

if (jeu.getCase(yArrive,xArrive)!=rien and jeu.getCase(yArrive,xArrive)!=cible)
{longeur=-2;return res;}

for (int i=0;i<jeu.getLargeur();i++)
  for (int j=0;j<jeu.getHauteur();j++)
  {
   carte[j][i]=-2; 
  }
  
  carte[jeu.getYperso()][jeu.getXperso()]=0;

listx.push_back(jeu.getXperso());listy.push_back(jeu.getYperso());
for (int i=0;i<jeu.getHauteur()*jeu.getLargeur()/2;i++)
{
  listxn.clear();listyn.clear();
  for (int j=0;j<listx.size();j++)
  {
   if (carte[listy[j]][listx[j]-1]==-2 and (jeu.getCase(listy[j],listx[j]-1)==rien or jeu.getCase(listy[j],listx[j]-1)==cible))
	{listxn.push_back(listx[j]-1);listyn.push_back(listy[j]);carte[listy[j]][listx[j]-1]=i+1;}
    
   if (carte[listy[j]][listx[j]+1]==-2 and (jeu.getCase(listy[j],listx[j]+1)==rien or jeu.getCase(listy[j],listx[j]+1)==cible))
	{listxn.push_back(listx[j]+1);listyn.push_back(listy[j]);carte[listy[j]][listx[j]+1]=i+1;}
	
   if (carte[listy[j]+1][listx[j]]==-2 and (jeu.getCase(listy[j]+1,listx[j])==rien or jeu.getCase(listy[j]+1,listx[j])==cible))
	{listxn.push_back(listx[j]);listyn.push_back(listy[j]+1);carte[listy[j]+1][listx[j]]=i+1;}
	
   if (carte[listy[j]-1][listx[j]]==-2 and (jeu.getCase(listy[j]-1,listx[j])==rien or jeu.getCase(listy[j]-1,listx[j])==cible))
	{listxn.push_back(listx[j]);listyn.push_back(listy[j]-1);carte[listy[j]-1][listx[j]]=i+1;}

  if (listx[j]==xArrive and listy[j]==yArrive)
  {
    i=jeu.getHauteur()*jeu.getLargeur();
  }
  }
  listx=listxn;listy=listyn;
  if (listx.size()==0)
     i=jeu.getHauteur()*jeu.getLargeur();
}

int compteur=carte[yArrive][xArrive];
longeur=compteur;
if (compteur==-2)
{ 
  return res;
}
int x,y;
x=xArrive;y=yArrive;
while (compteur!=0)
{
  if (carte[y][x-1]==compteur-1)
  {res.ajouterCoupDebut(droite); x--;compteur--;}
  
  if (carte[y][x+1]==compteur-1)
  {res.ajouterCoupDebut(gauche); x++;compteur--;}
  
  if (carte[y+1][x]==compteur-1)
  {res.ajouterCoupDebut(haut); y++;compteur--;}
  
  if (carte[y-1][x]==compteur-1)
  {res.ajouterCoupDebut(bas); y--;compteur--;}
}
return res;
}




int dijsktraSokoban::distanceCaisseCible(JeuSokoban &jeu, int xcaisse,int ycaisse)
{
  int carte[1000][1000];
vector<int> listx,listy;
vector<int> listxn,listyn;
SolutionSokoban res(&jeu);



for (int i=0;i<jeu.getLargeur();i++)
  for (int j=0;j<jeu.getHauteur();j++)
  {
   carte[j][i]=-2; 
  }
  
  carte[ycaisse][xcaisse]=0;

listx.push_back(xcaisse);listy.push_back(ycaisse);
for (int i=0;i<jeu.getHauteur()*jeu.getLargeur()/2;i++)
{
  listxn.clear();listyn.clear();
  for (int j=0;j<listx.size();j++)
  {
   if (carte[listy[j]][listx[j]-1]==-2 and (jeu.getCase(listy[j],listx[j]-1)==rien or jeu.getCase(listy[j],listx[j]-1)==cible))
	{listxn.push_back(listx[j]-1);listyn.push_back(listy[j]);carte[listy[j]][listx[j]-1]=i+1;}
    
   if (carte[listy[j]][listx[j]+1]==-2 and (jeu.getCase(listy[j],listx[j]+1)==rien or jeu.getCase(listy[j],listx[j]+1)==cible))
	{listxn.push_back(listx[j]+1);listyn.push_back(listy[j]);carte[listy[j]][listx[j]+1]=i+1;}
	
   if (carte[listy[j]+1][listx[j]]==-2 and (jeu.getCase(listy[j]+1,listx[j])==rien or jeu.getCase(listy[j]+1,listx[j])==cible))
	{listxn.push_back(listx[j]);listyn.push_back(listy[j]+1);carte[listy[j]+1][listx[j]]=i+1;}
	
   if (carte[listy[j]-1][listx[j]]==-2 and (jeu.getCase(listy[j]-1,listx[j])==rien or jeu.getCase(listy[j]-1,listx[j])==cible))
	{listxn.push_back(listx[j]);listyn.push_back(listy[j]-1);carte[listy[j]-1][listx[j]]=i+1;}

  if (jeu.getCase(listy[j],listx[j])==cible)
  {
    return i;
  }
  }
  listx=listxn;listy=listyn;
  if (listx.size()==0)
     i=jeu.getHauteur()*jeu.getLargeur();
}
return -1;
  
}

SolutionSokoban dijsktraSokoban::meilleurCheminCaisseCible(JeuSokoban& jeu, int xcaisse, int ycaisse)
{
    int carte[1000][1000];
vector<int> listx,listy;
vector<int> listxn,listyn;
SolutionSokoban res(&jeu);
int xArrive=-1,yArrive=-1;


for (int i=0;i<jeu.getLargeur();i++)
  for (int j=0;j<jeu.getHauteur();j++)
  {
   carte[j][i]=-2; 
  }
  
  carte[ycaisse][xcaisse]=0;

listx.push_back(xcaisse);listy.push_back(ycaisse);
for (int i=0;i<jeu.getHauteur()*jeu.getLargeur()/2;i++)
{
  listxn.clear();listyn.clear();
  for (int j=0;j<listx.size();j++)
  { if (carte[listy[j]+1][listx[j]]==-2 and (jeu.getCase(listy[j]+1,listx[j])==rien or jeu.getCase(listy[j]+1,listx[j])==cible))
	{listxn.push_back(listx[j]);listyn.push_back(listy[j]+1);carte[listy[j]+1][listx[j]]=i+1;}
	
   if (carte[listy[j]-1][listx[j]]==-2 and (jeu.getCase(listy[j]-1,listx[j])==rien or jeu.getCase(listy[j]-1,listx[j])==cible))
	{listxn.push_back(listx[j]);listyn.push_back(listy[j]-1);carte[listy[j]-1][listx[j]]=i+1;}
	
   if (carte[listy[j]][listx[j]-1]==-2 and (jeu.getCase(listy[j],listx[j]-1)==rien or jeu.getCase(listy[j],listx[j]-1)==cible))
	{listxn.push_back(listx[j]-1);listyn.push_back(listy[j]);carte[listy[j]][listx[j]-1]=i+1;}
    
   if (carte[listy[j]][listx[j]+1]==-2 and (jeu.getCase(listy[j],listx[j]+1)==rien or jeu.getCase(listy[j],listx[j]+1)==cible))
	{listxn.push_back(listx[j]+1);listyn.push_back(listy[j]);carte[listy[j]][listx[j]+1]=i+1;}
	
  

  if (jeu.getCase(listy[j],listx[j])==cible)
  {
    yArrive=listy[j];xArrive=listx[j];
    carte[yArrive][xArrive]=i;
    i=jeu.getHauteur()*jeu.getLargeur();
    break;
  }
  }
  listx=listxn;listy=listyn;
  if (listx.size()==0)
     i=jeu.getHauteur()*jeu.getLargeur();
}

if (xArrive==-1 or yArrive==-1)
{ 
  return res;
}

int compteur=carte[yArrive][xArrive];

int x,y;
x=xArrive;y=yArrive;
while (compteur!=0)
{
  if (carte[y+1][x]==compteur-1)
  {res.ajouterCoupDebut(haut); y++;compteur--;}
  
  if (carte[y-1][x]==compteur-1)
  {res.ajouterCoupDebut(bas); y--;compteur--;}
  
  if (carte[y][x+1]==compteur-1)
  {res.ajouterCoupDebut(gauche); x++;compteur--;}
  
  if (carte[y][x-1]==compteur-1)
  {res.ajouterCoupDebut(droite); x--;compteur--;}
  

}
return res;

}


