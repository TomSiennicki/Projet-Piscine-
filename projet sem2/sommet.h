#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <vector>
#include "svgfile.h"
class Sommet
{
    protected :
        ///int m_dist;
        ///Sommet* m_pere;
        int m_id;
        char m_nom;
        int m_x, m_y;
        std::vector <Sommet*> m_succ;

    public :
        Sommet(int id, char nom, int x, int y);
        void ecrire_som();
        int getId();
        void afficher_som(Svgfile&svg);
        int getx();
        int gety();
        char getNom();
        void setSucc(Sommet* succ);
       // void degre();
        // void degreNormal();
        /*int getDist();
        Sommet* getPere();
        void setDist(int dist);
        void setPere(Sommet* pere);*/

};



#endif // SOMMET_H_INCLUDED
