#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <vector>
#include "svgfile.h"
#include <map>

class Sommet
{
    protected :
        int m_id;
        char m_nom;
        int m_x, m_y;
        float m_distance;
        bool m_marque;
        std::map <Sommet*, float> m_succ;
        Sommet* m_pred;
        float m_indice; /// vecteur propre
        float m_degre, m_degreNormal;
        float m_sommeIndSucc;
        float m_Proximite;
        float m_proxNorm;
        float m_intermediaire;
        float m_intermediaireNorm;
        float m_idPCC;
        int m_couleur;
        Sommet*m_pere;

    public :
        Sommet(int id, char nom, int x, int y);
        void ecrire_som();
        int getId();
        void afficher_som(Svgfile&svg, int choix);
        int getx();
        int gety();
        char getNom();
        std::map<Sommet*, float> getSucc();
        void setSucc(Sommet* succ, float poids);
        float degre();
        void setDegreNormal(float degN);
        void reset();
        float getDistance();
        void setDistance(float distance);
        bool getMarque();
        void setMarque(bool m);
        void setPred(Sommet* succ);
        void setIndice(float a);
        float getIndice();
        void sommeIndiceSucc();
        float getSommeIndSucc();
        float getProximite();
        void setProximite(float s);
        Sommet* dijkstraSucc();
        void setProxNorm(float a);
        float getProxNorm();
        float getIntermediaire();
        void setIntermediaire(float interm);
        float getIntermediaireNorm();
        void setIntermediaireNorm(float interm);
        void reinitSucc();
        int getCouleur();
        void setCouleur(int c);
        Sommet* getPere();
        void setPere(Sommet* s);
        void affichSucc();
};



#endif // SOMMET_H_INCLUDED
