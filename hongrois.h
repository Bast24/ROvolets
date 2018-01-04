#ifndef HONGROIS_H
#define HONGROIS_H


#include "SharedElements.h"
#include "ressources.h"


class dimensionVolet {
    int index;

    int hautgond2;
    int gond2bas;
    int hautgond1;
    int gond1bas;
}

class dimensionFenetre {
    int index;

    int hautgond2g;
    int gond2basg;
    int hautgond1g;
    int gond1basg;

    int hautgond2d;
    int gond2basd;
    int hautgond1d;
    int gond1basd;
}




MapSolutions solutions;
MapSolutions bestSolutions;

MapFenetres fenetres;
MapVolets gauches;
MapVolets droits;






map <int,int> affectationVoletDroit;
map <int,int> affectationVoletGauche;
map <int,int> affectationFenetre;


map <int,dimensionVolet> clDroits;
map <int,dimensionVolet> clGauches;
map <int,dimensionFenetre> clFenetres;



int taileCluster=50;

int nombreCluster=1;



float distance(dimensionVolet tempVol1, dimensionVolet tempVol2) {
    float dist=0;
    dist += max(tempvol2.hautgond2-tempVol1.hautgond2,
                 tempvol1.hautgond2-tempVol2.hautgond2);
    dist+= max(tempvol2.gond2bas-tempVol1.gond2bas,
                 tempvol1.gond2bas-tempVol2.gond2bas);
    dist+= max(tempvol2.hautgond1-tempVol1.hautgond1,
                 tempvol1.hautgond1-tempVol2.hautgond1);
    dist+= max(tempvol2.gond1bas-tempVol1.gond1bas,
                 tempvol1.gond1bas-tempVol2.gond1bas);

    dist=float(pow(dist,1/4));
    return (dist);

}


void Clustering() {

    dimensionFenetre test1;
    dimensionVolet test2;

    for (int i=0; i<gauches.length(); i++) {

        test2.index=gauches[i].index;
        test2.hautgond2=gauches[i].hauteurGondSommet+gauches[i].hauteurInterGonds;
        test2.gond2bas=gauches[i].hauteurTotale - gauches[i].hauteurGondSommet - gauches[i].hauteurInterGonds;
        test2.hautgond1=gauches[i].hauteurGondSommet;
        test2.gond1bas=gauches[i].hauteurTotale - gauches[i].hauteurGondSommet;
        clGauches.insert(std::pair<int,dimensionVolet>(i,test2));


        test2.index=droits[i].index;
        test2.hautgond2=droits[i].hauteurGondSommet+droits[i].hauteurInterGonds;
        test2.gond2bas=droits[i].hauteurTotale - droits[i].hauteurGondSommet - droits[i].hauteurInterGonds;
        test2.hautgond1=droits[i].hauteurGondSommet;
        test2.gond1bas=droits[i].hauteurTotale - droits[i].hauteurGondSommet;
        clDroits.insert(std::pair<int,dimensionVolet>(i,test2))

        test1.index=fenetres[i].index;
        test1.hautgond2g=fenetres[i].hauteurGondSommetGauche+fenetres[i].hauteurInterGondsGauche;
        test1.gond2basg=fenetres[i].hauteurTotale - fenetres[i].hauteurGondSommetGauche - fenetres[i].hauteurInterGondsGauche;
        test1.hautgond1g=fenetres[i].hauteurGondSommetGauche;
        test1.gond1basg=fenetres[i].hauteurTotale - fenetres[i].hauteurGondSommetGauche;

        test1.hautgond2d=fenetres[i].hauteurGondSommetDroit+fenetres[i].hauteurInterGondsDroit;
        test1.gond2basd=fenetres[i].hauteurTotale - fenetres[i].hauteurGondSommetDroit - fenetres[i].hauteurInterGondsDroit;
        test1.hautgond1d=fenetres[i].hauteurGondSommetDroit;
        test1.gond1basd=fenetres[i].hauteurTotale - fenetres[i].hauteurGondSommetDroit;
        clDroits.insert(std::pair<int,dimensionVolet>(i,test1))
    }
    float deltaCout=10;
    float Cout=100000;
    float ancienCout=150000;
    while (deltaCout>5) {

        ancienCout=Cout;
        Cout=0;

    }



}


void Hongrois(string cheminz, string fenetresFile, string gauchesFile, string droitsFile) {



    readCsvToMap<Fenetre>(fenetres, fenetresFile);

    readCsvToMap<Volet>(gauches, gauchesFile);

    readCsvToMap<Volet>(droits, droitsFile);

    if fenetres.length()>tailleCluster {
            nombreCluster=int(fenetres.length()/tailleCluster);


    }

}

void matriceCout(string cheminz, string fenetresFile, string gauchesFile, string droitsFile)



#endif // HONGROIS_H
