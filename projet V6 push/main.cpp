#include <iostream>
#include <fstream>
#include "sommet.h"
#include "graphe.h"
#include <string>
#include "svgfile.h"

void menu()
{
    int choix0;
    //std::string fichier;
    std::string nom_fich;
    std::string pond;
    do
    {
        std::cout<<"Quel fichier de topologie voulez vous ouvrir ?"<<std::endl;
        std::cout<<"1.          graphe_etoile1_topo"<<std::endl;
        std::cout<<"2.          graphe_etoile3_topo"<<std::endl;
        std::cout<<"3.          graphe_cycle4_topo"<<std::endl;
        std::cout<<"4.          graphe_cycle5_topo"<<std::endl;
        std::cin>>choix0;

    }while(choix0>4 || choix0<1);

    switch(choix0)
    {
        case 1 :
            nom_fich="graphe_etoile1_topo.txt";
            break;
        case 2 :
            nom_fich="graphe_etoile3_topo.txt";
            break;
        case 3 :
            nom_fich="graphe_cycle4_topo.txt";
            break;
        case 4 :
            nom_fich="graphe_cycle5_topo.txt";
            break;
    }

    Graphe G(nom_fich);
    G.ecrire_som();
    /*Svgfile svg;#include <math.h>
    svg.addGrid();#include <math.h>
    G.afficher_gr(svg);*/
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
        std::cout<<"10.         AFFICHER LA CENTRALITE INTERMEDIAIRE"<<std::endl;
        std::cout<<"11.         AFFICHER LA CENTRALITE INTERMEDIAIRE NORMALISEE"<<std::endl;
        std::cout<<"12.         SUPPRIMER ARETE(S)"<<std::endl;
        std::cout<<"13.         SAUVEGARDER"<<std::endl;

        std::cin>>choix;
        if(choix == 2)
        {
            switch(choix0)
            {
                case 1 :
                    std::cout<<"Choisissez le fichier de ponderation"<<std::endl;
                    std::cout<<"1/ graphe_etoile1_ponde"<<std::endl;
                    std::cout<<"2/ graphe_etoile1_ponde2"<<std::endl;
                    std::cin>>choix2;
                    if(choix2==1)
                        pond = "graphe_etoile1_ponde.txt";
                    if(choix2==2)
                        pond = "graphe_etoile1_ponde2.txt";
                    break;
                case 2 :
                    std::cout<<"Choisissez le fichier de ponderation"<<std::endl;
                    std::cout<<"1/ graphe_etoile3_ponde"<<std::endl;
                    std::cout<<"2/ graphe_etoile3_ponde2"<<std::endl;
                    std::cin>>choix2;
                    if(choix2==1)
                        pond = "graphe_etoile3_ponde.txt";
                    if(choix2==2)
                        pond = "graphe_etoile3_ponde2.txt";
                    break;
                case 3 :
                    std::cout<<"Choisissez le fichier de ponderation"<<std::endl;
                    std::cout<<"1/ graphe_cycle4_ponde"<<std::endl;
                    std::cout<<"2/ graphe_cycle4_ponde2"<<std::endl;
                    std::cin>>choix2;
                    if(choix2==1)
                        pond = "graphe_cycle4_ponde.txt";
                    if(choix2==2)
                        pond = "graphe_cycle4_ponde2.txt";
                    break;
                case 4 :
                    std::cout<<"Choisissez le fichier de ponderation"<<std::endl;
                    std::cout<<"1/ graphe_cycle5_ponde"<<std::endl;
                    std::cout<<"2/ graphe_cycle5_ponde2"<<std::endl;
                    std::cin>>choix2;
                    if(choix2==1)
                        pond = "graphe_cycle5_ponde.txt";
                    if(choix2==2)
                        pond = "graphe_cycle5_ponde2.txt";
                    break;
            }

                G.ponderation(pond);
                G.creaSuccSommet();
                G.ecrire_som();
                G.affich();
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
        if(choix == 13)
        {
            G.sauvegarde();
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
            if(G.verifPoids())
            {
                G.intermediaire();
            }
        }

        if(choix == 11)
        {
            if(G.verifPoids())
            {
                G.intermediaireNorm();
            }
        }

        if(choix == 12)
        {
            if(G.verifPoids())
            {
                G.creaSuccSommet();
                G.centreAvSuppr();
                G.enleverArete();
            }
        }

        if(choix == 13)
        {
            G.sauvegarde();
        }

        Svgfile svg;
        svg.addGrid();
        G.afficher_gr(svg, choix);
    }

}

int main()
{
    menu();
    //G.ecrire_som();

    return 0;
}
