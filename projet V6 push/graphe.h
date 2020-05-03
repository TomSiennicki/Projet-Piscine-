#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include <vector>
#include <fstream>
#include "sommet.h"
#include <string>
#include "arc.h"
#include "svgfile.h"
#include <math.h>
#include <queue>
#include <stack>
class Graphe
{
protected :
    int m_orient;
    std::vector<Sommet*> m_sommets;
    int m_ordre;
    int m_taille;
    std::vector<Arete*> m_aretes;
    std::vector<std::vector<float>>m_tousInd;
    bool m_connexe;
    ///std::vector<std::vector<Sommet>> m_chemins;
public :
    Graphe();
    Graphe(std::string nom_fich);
    void ecrire_som();
    void afficher_gr(Svgfile&svg, int choix);
    void ponderation(std::string nom_fich);
    int getOrdre();
    void creaSuccSommet();
    void centreDeg();
    void centreDegNormal();
    void ponderationNulle();
    void vecteurPropre();
    void affichageVecteurPropre();
    void affichageVecteurPropreNormal();
    void centreProximite();
    void dijkstra(Sommet* s0);
    void centreProxNorm();
    bool verifPoids();
    void sauvegarde();
    void printpath(std::vector<Sommet*>& path, int & i, std::vector<std::vector<Sommet*>> & chemins);
    bool isNotVisited(int id, std::vector<Sommet*>& path);
    void findpaths(Sommet* src, Sommet* dst, Sommet* pointDePassage);
    void affich();
    void centreIntermediaire(Sommet* pointDePassage, std::vector<std::vector<Sommet*>> chemins, std::vector<int> idPCC);
    void intermediaire();
    void intermediaireNorm();
    void enleverArete();
    void centreAvSuppr();
    void reinitSuccSom();
    //std::vector<int> DFS(int num_s0)const;
    void afficher_parcours(const std::vector<int>& arbre);
    void DFS();
};

#endif // GRAPHE_H_INCLUDED
