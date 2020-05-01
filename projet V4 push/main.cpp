#include <iostream>
#include <fstream>
#include "sommet.h"
#include "graphe.h"
#include <string>
#include "svgfile.h"

void menu()
{

    std::string fichier;
    std::string nom_fich="grapheT2.txt";
    Graphe G(nom_fich);
    G.ecrire_som();
    /*Svgfile svg;#include <math.h>
    svg.addGrid();#include <math.h>
    G.afficher_gr(svg);*/
    ///G.creaSuccSommet();#include <math.h>
    int choix, choix2;


    /*                              PONDERATION             */

    while (choix!=1)
    {
        std::cout<<"QUE VOULEZ-VOUS FAIRE?"<<std::endl;
        std::cout<<"1.          QUITTER"<<std::endl;
        std::cout<<"2.          CHARGER UN FICHIER DE PONDERATION"<<std::endl;
        std::cout<<"3.          AFFICHER LA CENTRALITE DE DEGRE DES SOMMETS"<<std::endl;
        std::cout<<"4.          AFFICHER LA CENTRALITE DE DEGRE NORMALISE DES SOMMETS"<<std::endl;
        std::cout<<"5.          REINITIALISER LA PONDERATION"<<std::endl;
        std::cout<<"6.          AFFICHER LA CENTRALITE DE VECTEUR PROPRE"<<std::endl;
        std::cout<<"7.          AFFICHER LA CENTRALITE DE VECTEUR PROPRE NORMALISE"<<std::endl;
        std::cout<<"8.          AFFICHER LA CENTRALITE DE PROXIMITE"<<std::endl;
        std::cout<<"9.          AFFICHER LA CENTRALITE DE PROXIMITE NORMALISEE"<<std::endl;
        std::cout<<"10.         SAUVEGARDER"<<std::endl;

        std::cin>>choix;
        if(choix == 2)
        {
            std::cout<<"Choisissez le fichier de ponderation"<<std::endl;
            std::cout<<"1/ fichier 1"<<std::endl;
            std::cin>>choix2;

            if(choix2==1)
            {
                G.ponderation("ponderationT2.txt");
                G.creaSuccSommet();
                G.ecrire_som();
                G.affich();
            }
        }

        /*                              CENTRALITE DEGRE             */

        if(choix == 3)
        {
            G.creaSuccSommet();
            G.centreDeg();
        }

        /*                              CENTRALITE DEGRE NORMALISE             */

        if(choix == 4)
        {
            G.creaSuccSommet();
            G.centreDegNormal();
        }

        if(choix == 5)
        {
            G.ponderationNulle();
            G.creaSuccSommet();
            G.ecrire_som();
        }
        if(choix == 6)
        {
            G.vecteurPropre();
            G.affichageVecteurPropre();
        }

        if(choix == 7)
        {
            G.vecteurPropre();
            G.affichageVecteurPropreNormal();
        }

        if(choix == 8)
        {
            if(G.verifPoids())
            {

                G.centreProximite();
            }
        }

        if(choix == 9)
        {
            if(G.verifPoids())
            {
                G.centreProxNorm();
            }
        }

        if(choix == 10)
        {
            G.sauvegarde();
        }

        Svgfile svg;
        svg.addGrid();
        G.afficher_gr(svg);
    }

}

int main()
{
    menu();
    //G.ecrire_som();

    return 0;
}
