#include <iostream>
#include <fstream>
#include "graphe.h"
#include "sommet.h"
#include <string>
#include <algorithm>
#include "arc.h"
#include <vector>

Graphe::Graphe(std::string nom_fich)
{
    int ids;
    char nom;
    int x,y;
    int ida,e,s;
    Arete*a;
    std::ifstream fichier (nom_fich);
    Sommet* s1;
    fichier>>m_orient;
    fichier>>m_ordre;
    for(int i=0; i<m_ordre; i++)
    {
        fichier>>ids;
        fichier>>nom;
        fichier>>x;
        fichier>>y;
        s1=new Sommet(ids, nom, x, y);
        m_sommets.push_back(s1);
    }
    fichier>>m_taille;
    for(int k=0; k<m_taille; k++)
    {
        fichier>>ida;
        fichier>>e;
        fichier>>s;
        a=new Arete(ida,m_sommets[e], m_sommets[s]);
        m_aretes.push_back(a);
    }
}

void Graphe::ponderation(std::string nom_fich)
{
    int id,t;
    float p;
    std::ifstream fichier (nom_fich);
    fichier>>t;
    for(int i=0; i<t; i++)
    {
        fichier>>id;
        fichier>>p;
        m_aretes[i]->setP(p);
    }
}

void Graphe::ecrire_som()
{
    std::cout<<"oriente : "<<m_orient<<std::endl;
    std::cout<<"ordre: "<<m_ordre<<std::endl;
    std::cout<<"taille : "<<m_taille<<std::endl;
    for(int i=0; i<m_sommets.size(); i++)
    {
        m_sommets[i]->ecrire_som();
    }
    for(int k=0; k<m_aretes.size(); k++)
    {
        m_aretes[k]->ecrire_ar();
    }
}

void Graphe::afficher_gr(Svgfile&svg)
{
    for(int i=0; i<m_sommets.size(); i++)
    {
        m_sommets[i]->afficher_som(svg);
    }
    for(int k=0; k<m_aretes.size(); k++)
    {
        m_aretes[k]->afficher_ar(svg);
    }
}
