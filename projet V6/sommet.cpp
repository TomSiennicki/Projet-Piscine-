#include <iostream>
#include "sommet.h"
#include <string>
#include <vector>
#include <algorithm>

Sommet::Sommet(int id, char nom, int x, int y)
{
    m_id = id;
    m_nom = nom;
    m_x =x;
    m_y = y;
    m_distance = -1;
    m_marque=false;
    m_degre=0;
    m_intermediaire=0;
}
void Sommet::ecrire_som()
{
    std::cout<<"Sommet : "<<m_id<<" "<<m_nom<<" "<<m_x<<" "<<m_y<<std::endl;
}

int Sommet::getId()
{
    return m_id;
}

int Sommet::getx()
{
    return m_x;
}

int Sommet::gety()
{
    return m_y;
}

void Sommet::afficher_som(Svgfile&svg)
{
    svg.addCircle(m_x*100, m_y*100, 1, 1, "black");
}

char Sommet::getNom()
{
    return m_nom;
}

void Sommet::setSucc(Sommet* succ, float poids)
{
    m_succ.insert(std::pair <Sommet*, float> (succ, poids));
}

float Sommet::degre()
{
    m_degre=m_succ.size();
    return m_degre;
}

void Sommet::setDegreNormal(float degN)
{
    m_degreNormal=degN;
}

float Sommet::getDistance()
{
    return m_distance;
}

void Sommet::setDistance(float distance)
{
    m_distance=distance;
}

bool Sommet::getMarque()
{
    return m_marque;
}


void Sommet::setPred(Sommet* succ)
{
    m_pred=succ;
}


void Sommet::setIndice(float a)
{
    m_indice = a;
}

float Sommet::getIndice()
{
    return m_indice;
}

float Sommet::getSommeIndSucc()
{
    return m_sommeIndSucc;
}

void Sommet::sommeIndiceSucc()
{
    m_sommeIndSucc=0;
    for (std::map<Sommet*,float>::iterator j = m_succ.begin() ; j != m_succ.end() ; j++)
    {
        m_sommeIndSucc += (j->first)->getIndice();
    }

}

float Sommet::getProximite()
{
    return m_Proximite;
}

void Sommet::reset()
         {
            m_distance = 10000;
            m_pred = nullptr;
            m_marque = false;
         }


void Sommet::setMarque(bool m)
{
    m_marque = m;
}

Sommet* Sommet::dijkstraSucc()
{
    Sommet * retour;
    for(std::map<Sommet*, float>::iterator i=m_succ.begin(); i!=m_succ.end(); ++i)
    {
        if((i->first)->getMarque() == false)
        {
            if(m_distance + (i->second) < (i->first)->getDistance())
            {
                (i->first)->setDistance(m_distance + (i->second));
                (i->first)->setPred(this);
                retour = (i->first);
            }
        }
    }
    return retour;
}

void Sommet::setProximite(float s)
{
    m_Proximite = s;
}
void Sommet::setProxNorm(float a)
{
    m_proxNorm = a;
}
float Sommet::getProxNorm()
{
    return m_proxNorm;
}

std::map<Sommet*, float> Sommet::getSucc()
{
    return m_succ;
}


float Sommet::getIntermediaire()
{
    return m_intermediaire;
}

void Sommet::setIntermediaire(float interm)
{
    m_intermediaire=interm;
}

float Sommet::getIntermediaireNorm()
{
    return m_intermediaireNorm;
}
void Sommet::setIntermediaireNorm(float interm)
{
    m_intermediaireNorm = interm;
}


void Sommet::reinitSucc()
{
    m_succ.clear();
}
