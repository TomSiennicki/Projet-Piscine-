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
      void setP(float p);
};

#endif // ARC_H_INCLUDED
