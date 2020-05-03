#include <iostream>
#include <fstream>
#include "sommet.h"
#include <string>
#include "arc.h"
#include <vector>

Arete::Arete(int ida, Sommet*s1, Sommet*s2)
{
    m_ida = ida;
    m_p = 0;
    m_s1 = s1;
    m_s2 = s2;
}

void Arete::ecrire_ar()
{
    std::cout<<"arete : "<<m_ida<<" "<<m_s1->getId()<<" "<<m_s2->getId()<<" "<<m_p<<std::endl;
}

void Arete::afficher_ar(Svgfile&svg)
{
    svg.addLine(m_s1->getx()*100, m_s1->gety()*100, m_s2->getx()*100, m_s2->gety()*100, "black");
    svg.addDisk(m_s1->getx()*100, m_s1->gety()*100, 5, "black");
    svg.addDisk(m_s2->getx()*100, m_s2->gety()*100, 5, "black");

}

void Arete::afficher_arEXT(Svgfile&svg)
{
    svg.addLine(5*m_s1->getx(), 5*m_s1->gety(), 5*m_s2->getx(), 5*m_s2->gety(), "black");
    svg.addDisk(m_s1->getx()*5, m_s1->gety()*5, 5, "black");
    svg.addDisk(m_s2->getx()*5, m_s2->gety()*5, 5, "black");


}

void Arete::setP(float p)
{
    m_p = p;
}

float Arete::getP()
{
    return m_p;
}

Sommet* Arete::getS1()
{
    return m_s1;
}

Sommet* Arete::getS2()
{
    return m_s2;
}

int Arete::getIda()
{
    return m_ida;
}
