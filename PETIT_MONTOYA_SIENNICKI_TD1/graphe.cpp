#include <iostream>
#include <fstream>
#include "graphe.h"
#include "sommet.h"
#include <string>
#include <algorithm>
#include "arc.h"


Graphe::Graphe()
{

}


Graphe::Graphe(std::string nom_fich, int choix0)
{
    int ids;
    int x,y;
    int ida,e,s;
    Arete*a;
    std::ifstream fichier (nom_fich);
    Sommet* s1;
    fichier>>m_orient;
    fichier>>m_ordre;

    if(choix0 == 5)
    {
       std::string nom;
    for(int i=0; i<m_ordre; i++)
    {
        fichier>>ids;
        fichier>>nom;
        fichier>>x;
        fichier>>y;
        s1=new Sommet(ids, nom, x, y);
        m_sommets.push_back(s1);
    }
    }

    else {
            char nom;
             for(int i=0; i<m_ordre; i++)
    {
        fichier>>ids;
        fichier>>nom;
        fichier>>x;
        fichier>>y;
        s1=new Sommet(ids, nom, x, y);
        m_sommets.push_back(s1);
    }
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

void Graphe::ecrire_som(int choix0)
{
    std::cout<<"oriente : "<<m_orient<<std::endl;
    std::cout<<"ordre: "<<m_ordre<<std::endl;
    std::cout<<"taille : "<<m_taille<<std::endl;
    for(unsigned int i=0; i<m_sommets.size(); i++)
    {
        m_sommets[i]->ecrire_som(choix0);
    }
    for(unsigned int k=0; k<m_aretes.size(); k++)
    {
        m_aretes[k]->ecrire_ar();
    }
}

void Graphe::afficher_gr(Svgfile&svg, int choix, int choix0)
{
    if(choix0==5)
    {
         for(unsigned int k=0; k<m_aretes.size(); k++)
    {
        m_aretes[k]->afficher_arEXT(svg);
    }
         for(unsigned int i=0; i<m_sommets.size(); i++)
    {
        m_sommets[i]->afficher_somEXT(svg, choix);
    }
    }

    else{
             for(unsigned int k=0; k<m_aretes.size(); k++)
    {
        m_aretes[k]->afficher_ar(svg);
    }
    for(unsigned int i=0; i<m_sommets.size(); i++)
    {
        m_sommets[i]->afficher_som(svg, choix);
    }
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
            if(m_aretes[j]->getS1()->getId() == m_sommets[i]->getId())
            {
                // on ajoute le sommet2 dans le vec de successeurs
                m_sommets[i]->setSucc(m_aretes[j]->getS2(), m_aretes[j]->getP());
            }

            /// comparer si dans l'arête en s1 on a le même sommet[i]
            if(m_aretes[j]->getS2()->getId() == m_sommets[i]->getId())
            {
                // on ajoute le sommet1 dans le vec de successeurs
                m_sommets[i]->setSucc(m_aretes[j]->getS1(), m_aretes[j]->getP());
            }
        }
    }

}


void Graphe::centreDeg()
{
    std::cout << "Centralite Degre : "<<std::endl;
    for(unsigned int i=0; i<m_sommets.size(); ++i)
    {
        std::cout << "Sommet " << m_sommets[i]->getNom() << " : " << m_sommets[i]->degre() << std::endl;
    }
    std::cout << std::endl;
}

void Graphe::centreDegNormal()
{
    std::cout << "Centralite Degre normalise : "<<std::endl;
    for(unsigned int i=0; i<m_sommets.size(); ++i)
    {
        std::cout << "Sommet " << m_sommets[i]->getNom() << " : " << (m_sommets[i]->degre())/((m_ordre)-1) << std::endl;
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
    std::cout<<"Vecteur Propre : "<<std::endl;
    for(unsigned int i =0; i<m_sommets.size(); i++)
    {
        std::cout<<"Sommet "<<m_sommets[i]->getNom()<<" : "<<m_sommets[i]->getIndice()<<std::endl;
    }
    std::cout << std::endl;
}

void Graphe::affichageVecteurPropreNormal()
{
    std::cout<<"Vecteur Propre Normalise : "<<std::endl;
    for(unsigned int i =0; i<m_sommets.size(); i++)
    {
        std::cout<<"Sommet "<<m_sommets[i]->getNom()<<" : "<<m_sommets[i]->getIndice() / (m_ordre -1)<<std::endl;
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
    }
    while(cp!=0);

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
    std::cout << "Centralite de proximite normalisee : "<<std::endl;
    for(unsigned int i=0; i<m_sommets.size(); i++)
    {
        dijkstra(m_sommets[i]);
        std::cout << "Sommet " << m_sommets[i]->getNom() << " : " << (m_sommets[i]->getProxNorm()) << std::endl;
    }
    std::cout << std::endl;
}

void Graphe::centreProximite()
{
    std::cout << "Centralite de proximite : "<<std::endl;
    for(unsigned int i=0; i<m_sommets.size(); i++)
    {
        dijkstra(m_sommets[i]);
        std::cout << "Sommet " << m_sommets[i]->getNom() << " : " << (m_sommets[i]->getProximite()) << std::endl;
    }
    std::cout << std::endl;
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
            flux<<" ";
            flux<<(m_sommets[i]->degre())/((m_ordre)-1);///degré non normalisé
            flux<<" ";
            flux<<m_sommets[i]->getIndice();/// vecteur propre
            flux<<" ";
            flux<<m_sommets[i]->getProximite();///proximité
            flux<<" ";
            flux<<m_sommets[i]->getProxNorm();///proximité Normalisée
            flux<<" ";
            flux<<m_sommets[i]->getIntermediaire();///intermediarité
            flux<<" ";
            flux<<m_sommets[i]->getIntermediaireNorm()<<std::endl;///intermediarité normalisée
        }

    }
}

/// SOURCE : https://www.geeksforgeeks.org/print-paths-given-source-destination-using-bfs/

// utility function for printing
// the found path in graph
void Graphe::printpath(std::vector<Sommet*>& path, int & i, std::vector<std::vector<Sommet*>> & chemins)
{
    chemins.push_back(std::vector<Sommet*>());
    for(unsigned int j =0; j<path.size(); j++)
    {
        chemins[i].push_back(path[j]);
    }
    // std::cout << std::endl;
    i++;

}

// utility function to check if current
// vertex is already present in path
bool Graphe::isNotVisited(int id, std::vector<Sommet*>& path)
{
    for (auto sommet: path)
        if (sommet->getId() == id)
            return false;

    return true;
}

// utility function for finding paths in graph
// from source to destination
void Graphe::findpaths(Sommet* src, Sommet* dst, Sommet* pointDePassage)
{
    float S=0;
    float mini;
    int compteurPcc=0;
    int i=0;
    std::vector<std::vector<Sommet*>> chemins;
    std::vector<float> poids;
    std::vector<int> idPCC;
    // create a queue which stores
    // the paths
    std::queue <std::vector<Sommet*>> q;

    // path vector to store the current path
    std::vector<Sommet*> path;
    path.push_back(src);
    q.push(path);

    while (!q.empty())
    {
        path = q.front();
        q.pop();
        Sommet* last = path[path.size() - 1];

        // if last vertex is the desired destination
        // then print the path
        if (last->getId() == dst->getId())
        {
            printpath(path, i, chemins);
        }


        // traverse to all the nodes connected to
        // current vertex and push new path to queue
        for(auto s : last->getSucc())
        {
            if(isNotVisited((s.first)->getId(), path))
            {
                std::vector<Sommet*> newpath(path);
                newpath.push_back(s.first);
                q.push(newpath);
            }

        }
    }

    for(unsigned int j =0; j<chemins.size(); ++j)
    {
        for (unsigned int k =0; k<chemins[j].size(); ++k)
        {
            for (unsigned int p =0; p<m_aretes.size(); ++p)
                if(k!=chemins[j].size()-1)
                {
                    if((chemins[j][k]->getId() == m_aretes[p]->getS1()->getId())  && chemins[j][k+1]->getId() == m_aretes[p]->getS2()->getId())
                    {
                        S+=m_aretes[p]->getP();
                    }

                    if(chemins[j][k]->getId() == m_aretes[p]->getS2()->getId()  && chemins[j][k+1]->getId() == m_aretes[p]->getS1()->getId())
                    {
                        S+=m_aretes[p]->getP();
                    }

                }
        }
        poids.push_back(S);
        S=0;
    }

    mini=*min_element(poids.begin(), poids.end());
    for(unsigned int j =0; j<poids.size(); j++)
    {
        if(poids[j] == mini)
            void reinitSuccSom();
        {
            compteurPcc++;
            idPCC.push_back(j);
        }
    }
    centreIntermediaire(pointDePassage, chemins, idPCC);

}
/// FIN DE L'UTILISATION DU CODE SOURCE

void Graphe::centreIntermediaire(Sommet* pointDePassage, std::vector<std::vector<Sommet*>> chemins, std::vector<int> idPCC)
{
    float cpt=0;
    for(unsigned int a=0; a<idPCC.size(); a++)
    {
        for(unsigned int b=0; b<chemins[idPCC[a]].size(); b++)
        {
            if(chemins[idPCC[a]][b]->getId() == pointDePassage->getId())
                cpt++;
        }
    }
    pointDePassage->setIntermediaire(pointDePassage->getIntermediaire()+(cpt/idPCC.size()));
}

void Graphe::affich()
{
    std::vector<Sommet*>Q;
    Sommet* a;
    Sommet* b;

    for(unsigned int i=0; i<m_sommets.size(); ++i)
    {
        for(unsigned int j=0; j<m_sommets.size(); ++j)
        {
            if(m_sommets[i]->getId() != m_sommets[j]->getId())
            {
                Q.push_back(m_sommets[j]);
            }
        }
        while(Q.size()!=1)
        {
            a=Q.back();
            for(unsigned int k=(Q.size()-1); k>0; --k)
            {
                b=Q[k];
                findpaths(a, b, m_sommets[i]);
            }
            Q.pop_back();
        }
    }


}

void Graphe::intermediaire()
{
    affich();
    std::cout <<"Centralite intermediaire :"<< std::endl;
    for(unsigned int i=0; i<m_sommets.size(); ++i)
    {
        std::cout <<"Sommet "<< m_sommets[i]->getNom() <<" : "<< m_sommets[i]->getIntermediaire()<< std::endl;
    }

}

void Graphe::intermediaireNorm()
{
    affich();
    std::cout <<"Centralite intermediaire normalisee :"<< std::endl;
    for(unsigned int i=0; i<m_sommets.size(); ++i)
    {
        m_sommets[i]->setIntermediaireNorm((2*(m_sommets[i]->getIntermediaire()))/(pow(m_ordre,2) -(3*m_ordre) +2));
        std::cout <<"Sommet "<< m_sommets[i]->getNom() <<" : "<< m_sommets[i]->getIntermediaireNorm()<< std::endl;
    }

}

void Graphe::reinitSuccSom()
{
    for(unsigned int i=0; i<m_sommets.size(); i++)
    {
        m_sommets[i]->reinitSucc();
    }
}

bool verifTemp(std::vector<unsigned int> indArSuppr, Arete*a)
{
    bool retour=true;
    for(size_t k=0; k<indArSuppr.size(); ++k)
    {
        if(a->getIda()==indArSuppr[k])
        {
            retour = false;
        }
    }
    return retour;
}

void Graphe::enleverArete(int choix0)
{
    int nbArSuppr;
    int a;
    std::vector<unsigned int> indArSuppr;
    std::vector<Arete*> temp;
    std::cout <<"Combien d'aretes voulez vous supprimer ?"<< std::endl;
    std::cin >>nbArSuppr;

    for(int k=0; k<nbArSuppr; ++k)
    {
        std::cout <<"Donner l'indice de l'arete a supprimer"<< std::endl;
        std::cin >>a;
        indArSuppr.push_back(a);
        m_taille--;
    }

    for(unsigned int p=0; p<m_aretes.size(); ++p)
    {
            if(verifTemp(indArSuppr, m_aretes[p]))
            {
                temp.push_back(m_aretes[p]);
            }
    }

    m_aretes.clear();

    for(unsigned int p=0; p<temp.size(); ++p)
    {
        m_aretes.push_back(temp[p]);
    }
    // Réinitialisert les successeurs dans chaque sommet
    reinitSuccSom();
    creaSuccSommet();
    ecrire_som(choix0);

    DFS();

    if(choix0!=5)
    {
    centreDeg();
    centreDegNormal();
    vecteurPropre();


    if(m_connexe)
    {
        centreProxNorm();
        centreProximite();
        affich();
    }

    ///affichage
    for(unsigned int i=0; i<m_sommets.size(); ++i)
    {
        std::cout<<m_sommets[i]->getNom()<<" : "<<std::endl;
        std::cout<<"Centralite degre : initiale = "<<m_tousInd[i][0]<<" finale : "<<m_sommets[i]->degre()<<std::endl;
        std::cout<<"Centralite degre Normalisee : initiale = "<<m_tousInd[i][1]<<" finale : "<<m_sommets[i]->degre()/(m_ordre-1)<<std::endl;
        std::cout<<"Centralite vecteur propre : initiale = "<<m_tousInd[i][2]<<" finale : "<<m_sommets[i]->getIndice()<<std::endl;
        std::cout<<"Centralite vecteur propre Normalisee : initiale = "<<m_tousInd[i][3]<<" finale : "<<m_sommets[i]->getIndice()/(m_ordre-1)<<std::endl;
        std::cout<<"Centralite proximite : initiale = "<<m_tousInd[i][4]<<" finale : "<<m_sommets[i]->getProximite()<<std::endl;
        std::cout<<"Centralite proximite Normalisee : initiale = "<<m_tousInd[i][5]<<" finale : "<<m_sommets[i]->getProxNorm()<<std::endl;
        std::cout<<"Centralite intermediaire : initiale = "<<m_tousInd[i][6]<<" finale : "<<m_sommets[i]->getIntermediaire()<<std::endl;
        std::cout<<"Centralite intermediaire Normalisee : initiale = "<<m_tousInd[i][7]<<" finale : "<<m_sommets[i]->getIntermediaireNorm()<<std::endl;
    }
    std::cout<<std::endl;
    }

    if(m_connexe)
    {

        std::cout<<"Le graphe est encore connexe"<<std::endl;
    }
    else
    {
        std::cout<<"Le graphe n'est plus connexe"<<std::endl;
    }
}

void Graphe::centreAvSuppr()
{
    centreDeg();
    centreDegNormal();
    centreProximite();
    centreProxNorm();
    vecteurPropre();
    affich();

    for(unsigned int i=0; i<m_sommets.size(); ++i)
    {
        m_tousInd.push_back(std::vector<float>());
        m_tousInd[i].push_back(m_sommets[i]->degre());
        m_tousInd[i].push_back(m_sommets[i]->degre()/(m_ordre-1));
        m_tousInd[i].push_back(m_sommets[i]->getIndice());
        m_tousInd[i].push_back(m_sommets[i]->getIndice()/(m_ordre-1));
        m_tousInd[i].push_back(m_sommets[i]->getProximite());
        m_tousInd[i].push_back(m_sommets[i]->getProxNorm());
        m_tousInd[i].push_back(m_sommets[i]->getIntermediaire());
        m_tousInd[i].push_back(m_sommets[i]->getIntermediaireNorm());
    }

}

void Graphe::DFS()  /// SOURCE CODE MADAME PALASI
{
    bool connexe=true;
    /// déclaration de la pile
    std::stack<Sommet*> pile;

    ///étape initiale : on enpile et on marque le sommet initial
    for(unsigned int i=0; i<m_sommets.size(); ++i)
    {
        m_sommets[i]->setCouleur(0);
        m_sommets[i]->setPere(nullptr);
    }
    pile.push(m_sommets[0]);
    m_sommets[0]->setCouleur(1);
    Sommet *s;

    ///tant que la pile n'est pas vide
    while(!pile.empty())
    {

        ///on dépile le prochain sommet
        s = pile.top();
        pile.pop();

        ///pour chaque successeur du sommet dépilé
        for(auto succ : s->getSucc())
        {
            if((succ.first)->getCouleur()==0)     ///s'il n'est pas marqué
            {
                pile.push(succ.first);
                (succ.first)->setCouleur(1);
                (succ.first)->setPere(s);
            }
        }
    }

    for(unsigned int i=0; i<m_sommets.size(); ++i)
    {
        if(m_sommets[i]->getCouleur()==0)
        {
            connexe = false;
        }
    }

    if(connexe)
    {
        m_connexe=true;
    }
    else
    {
        m_connexe=false;
    }
}
