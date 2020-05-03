#ifndef ARC_H_INCLUDED
#define ARC_H_INCLUDED
#include "sommet.h"
#include <string>
#include <vector>
#include "svgfile.h"
class Arete
{
    protected :
      int m_ida;
      float m_p;
      Sommet*m_s1;
      Sommet*m_s2;
    public :
      Arete(int ida, Sommet*s1, Sommet*s2);
      void ecrire_ar();
      void afficher_ar(Svgfile&svg);
      void afficher_arEXT(Svgfile&svg);
      void setP(float p);
      float getP();
      Sommet* getS1();
      Sommet* getS2();
      int getIda();
};

#endif // ARC_H_INCLUDED
