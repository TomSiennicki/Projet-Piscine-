#include <iostream>
#include <fstream>
#include "sommet.h"
#include "graphe.h"
#include <string>

std::string menu(Graphe G)
{
    int a,b;
    std::string fichier;
    std::cout<<"Voulez vous une ponderation ?"<<std::endl;
    std::cout<<"1/ Oui"<<std::endl;
    std::cout<<"2/ Non"<<std::endl;
    std::cin<<a;
    if(a == 1)
    {
        std::cout<<"Choisissez le fichier de ponderation"<<std::endl;
        std::cout<<"1/ fichier 1"<<std::endl;
        std::cin<<b;

        if(b==1)
        {

        }

    }
}

int main()
{
    std::string nom_fich="graphe.txt";
    Graphe G(nom_fich);
    G.ecrire_som();

    Svgfile svg;
    svg.addGrid();


    G.afficher_gr(svg);
    return 0;
}
