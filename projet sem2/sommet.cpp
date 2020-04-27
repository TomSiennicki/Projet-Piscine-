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

