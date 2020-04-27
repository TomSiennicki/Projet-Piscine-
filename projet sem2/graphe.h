#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include <vector>
#include <fstream>
#include "sommet.h"
#include <string>
#include "arc.h"
#include "svgfile.h"
class Graphe
{
    protected :
      int m_orient;
      std::vector<Sommet*> m_sommets;
      int m_ordre;
      int m_taille;
      std::vector<Arete*> m_aretes;
    public :
      Graphe(std::string nom_fich);
      void ecrire_som();
      void afficher_gr(Svgfile&svg);
      void ponderation(std::string nom_fich);
      int getOrdre();
      void creaSuccSommet();
};

#endif // GRAPHE_H_INCLUDED
