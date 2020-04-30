#include <iostream>
#include <fstream>
#include "graphe.h"
#include "sommet.h"
#include <string>
#include <algorithm>
#include "arc.h"
#include <vector>

Graphe::Graphe()
{

}

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

void Graphe::ponderationNulle()
{
    for(unsigned int i=0; i<m_aretes.size(); i++)
    {
        m_aretes[i]->setP(0);
    }
}

void Graphe::ecrire_som()
{
    std::cout<<"oriente : "<<m_orient<<std::endl;
    std::cout<<"ordre: "<<m_ordre<<std::endl;
    std::cout<<"taille : "<<m_taille<<std::endl;
    for(unsigned int i=0; i<m_sommets.size(); i++)
    {
        m_sommets[i]->ecrire_som();
    }
    for(unsigned int k=0; k<m_aretes.size(); k++)
    {
        m_aretes[k]->ecrire_ar();
    }
}

void Graphe::afficher_gr(Svgfile&svg)
{
    for(unsigned int i=0; i<m_sommets.size(); i++)
    {
        m_sommets[i]->afficher_som(svg);
    }
    for(unsigned int k=0; k<m_aretes.size(); k++)
    {
        m_aretes[k]->afficher_ar(svg);
    }
}

int Graphe::getOrdre()
{
    return m_ordre;
}

void Graphe::creaSuccSommet()
{

    for(unsigned int i=0; i<m_sommets.size(); i++)
    {
        for(unsigned int j=0; j<m_aretes.size(); j++)
        {
            /// comparer si dans l'arête en s1 on a le même sommet[i]
            if(m_aretes[j]->getS1()->getNom() == m_sommets[i]->getNom())
            {
                // on ajoute le sommet2 dans le vec de successeurs
                m_sommets[i]->setSucc(m_aretes[j]->getS2(), m_aretes[j]->getP());
            }

            /// comparer si dans l'arête en s1 on a le même sommet[i]
            if(m_aretes[j]->getS2()->getNom() == m_sommets[i]->getNom())
            {
                // on ajoute le sommet1 dans le vec de successeurs
                m_sommets[i]->setSucc(m_aretes[j]->getS1(), m_aretes[j]->getP());
            }
        }
    }

}


void Graphe::centreDeg()
{
    for(unsigned int i=0; i<m_sommets.size(); ++i)
    {
        std::cout << "Centrabilite Degre Sommet " << m_sommets[i]->getNom() << " : " << m_sommets[i]->degre() << std::endl;
    }
    std::cout << std::endl;
}

void Graphe::centreDegNormal()
{
    for(unsigned int i=0; i<m_sommets.size(); ++i)
    {
        std::cout << "Centrabilite Degre Normalise Sommet " << m_sommets[i]->getNom() << " : " << (m_sommets[i]->degre())/((m_ordre)-1) << std::endl;
        m_sommets[i]->setDegreNormal((m_sommets[i]->degre())/((m_ordre)-1));
    }
    std::cout << std::endl;
}

void Graphe::vecteurPropre()
{
    float lambda=0, lambdapred=0;
    double S = 0;
    /// initialisation
    for(unsigned int i =0; i<m_sommets.size(); i++)
    {
        m_sommets[i]->setIndice(1);
    }

    do
    {
        lambdapred = lambda;
        for(unsigned int i =0; i<m_sommets.size(); i++)
        {
            m_sommets[i]->sommeIndiceSucc();
        }
        for(unsigned int i =0; i<m_sommets.size(); i++)
        {
            S += ((m_sommets[i]->getSommeIndSucc())*(m_sommets[i]->getSommeIndSucc()));
        }
        lambda = sqrt(S);

        S=0;
        for(unsigned int i =0; i<m_sommets.size(); i++)
        {
            m_sommets[i]->setIndice(m_sommets[i]->getSommeIndSucc()/lambda);
        }
    }
    while((lambda-lambdapred)>0.01);
}

void Graphe::affichageVecteurPropre()
{
    std::cout<<"Vecteur Propre "<<std::endl;
    for(unsigned int i =0; i<m_sommets.size(); i++)
    {
        std::cout<<"sommet "<<m_sommets[i]->getNom()<<" : "<<m_sommets[i]->getIndice()<<std::endl;
    }
    std::cout << std::endl;
}

void Graphe::affichageVecteurPropreNormal()
{
    std::cout<<"Vecteur Propre Normalise"<<std::endl;
    for(unsigned int i =0; i<m_sommets.size(); i++)
    {
        std::cout<<"sommet "<<m_sommets[i]->getNom()<<" : "<<m_sommets[i]->getIndice() / (m_ordre -1)<<std::endl;
    }
    std::cout << std::endl;
}


void Graphe::dijkstra(Sommet* s0)
{
    float S=0;
    Sommet* origine = nullptr;
    for(unsigned int i=0; i<m_sommets.size(); ++i)
    {
        m_sommets[i]->reset();
    }
    s0->setDistance(0);
    origine=s0;
    int cp = m_sommets.size();
    do
    {
        origine->setMarque(true);
        origine = origine->dijkstraSucc();
        cp--;
    }while(cp!=0);

    for(unsigned int i=0; i<m_sommets.size(); ++i)
    {
        S += m_sommets[i]->getDistance();
        s0->setProximite(1/S);
        s0->setProxNorm((m_ordre-1)/S);
    }
}

bool Graphe::verifPoids()
{
    if(m_aretes[0]->getP()==0)
    {
        std::cout << "Veuillez charger un fichier de ponderation !!"<< std::endl;
        return false;
    }
    else
    {

        return true;
    }
}

void Graphe::centreProxNorm()
{
    for(unsigned int i=0; i<m_sommets.size(); i++)
    {
        dijkstra(m_sommets[i]);
        std::cout << "Sommet " << m_sommets[i]->getNom() << " : " << (m_sommets[i]->getProxNorm()) << std::endl;
    }
}

void Graphe::centreProximite()
{
    for(unsigned int i=0; i<m_sommets.size(); i++)
    {
        dijkstra(m_sommets[i]);
        std::cout << "Sommet " << m_sommets[i]->getNom() << " : " << (m_sommets[i]->getProximite()) << std::endl;
    }
}

void Graphe::sauvegarde()
{
    std::string fichier("sauvegarde.txt");
    std::ofstream flux(fichier.c_str());
    if(flux)
    {
        for(unsigned int i=0; i<m_sommets.size(); i++)
        {
            flux<<m_sommets[i]->getId();
            flux<<" ";
            flux<<m_sommets[i]->degre();///degré normalisé
            flux<<"-";
            flux<<(m_sommets[i]->degre())/((m_ordre)-1);///degré non normalisé
            flux<<" ";
            flux<<m_sommets[i]->getIndice();/// vecteur propre
            flux<<" ";
            flux<<m_sommets[i]->getProximite();///proximité
            flux<<"-";
            flux<<m_sommets[i]->getProxNorm()<<std::endl;///proximité Normalisée
        }

    }
}

/// CITER LA SOURCE

// utility function for printing
// the found path in graph
void Graphe::printpath(std::vector<Sommet>& path)
{
    for (auto sommet: path)
    {
        std::cout << sommet.getNom() << " ";
    }
    std::cout << std::endl;

}

// utility function to check if current
// vertex is already present in path
bool Graphe::isNotVisited(int id, std::vector<Sommet>& path)
{
    for (auto sommet: path)
        if (sommet.getId() == id)
            return false;

    return true;
}

// utility function for finding paths in graph
// from source to destination
void Graphe::findpaths(Sommet src, Sommet dst)
{
    // create a queue which stores
    // the paths
    std::queue <std::vector<Sommet>> q;

    // path vector to store the current path
    std::vector<Sommet> path;
    path.push_back(src);
    q.push(path);

    while (!q.empty()) {
        path = q.front();
        q.pop();
        Sommet last = path[path.size() - 1];

        // if last vertex is the desired destination
        // then print the path
        if (last.getId() == dst.getId())
            printpath(path);

        // traverse to all the nodes connected to
        // current vertex and push new path to queue
        for(auto s : last.getSucc())
        {
            if(isNotVisited((s.first)->getId(), path))
               {
                   std::vector<Sommet> newpath(path);
                   newpath.push_back(*(s.first));
                   q.push(newpath);
               }

        }
       /* for (int i = 0; i < g[last].size(); i++) {
            if (isNotVisited(g[last][i], path)) {
                vector<int> newpath(path);
                newpath.push_back(g[last][i]);
                q.push(newpath);
            }
        } */
    }
}

void Graphe::affich()
{
    findpaths(*m_sommets[0], *m_sommets[3]);
}
