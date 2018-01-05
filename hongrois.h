#ifndef HONGROIS_H
#define HONGROIS_H


#include "SharedElements.h"
#include "ressources.h"
#include <algorithm>

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


class cluster {
    dimensionFenetre noyau;

    vector<int> droits;
    vector<int> gauches;
    vector<int> fenetres;

};


vector<cluster> clusters;

MapSolutions solutions;
MapSolutions bestSolutions;

MapFenetres fenetres;
MapVolets gauches;
MapVolets droits;





map <int,int> affectationVoletDroit;
map <int,int> affectationVoletGauche;
map <int,int> affectationFenetre;


vector <dimensionVolet> clDroits;
vector <dimensionVolet> clGauches;
vector <dimensionFenetre> clFenetres;

map <int,dimensionFenetre> fenetresTemp;
map <int,dimensionVolet> gauchesTemp;
map <int,dimensionVolet> droitsTemp;



int taileCluster=50;

int nombreCluster=1;


dimensionFenetre FusionVolet(dimensionVolet droit, dimensionVolet gauche) {
    dimensionFenetre temp;
    temp.index=droit.index;

    temp.hautgond2g=gauche.hautgond2;
    temp.gond2basg=gauche.gond2bas;
    temp.hautgond1g=gauche.hautgond1;
    temp.gond1basg=gauche.gond1bas;

    temp.hautgond2d=droit.hautgond2;
    temp.gond2basd=droit.gond2bas;
    temp.hautgond1d=droit.hautgond1;
    temp.gond1basd=droit.gond1bas;

    return(temp);
}


float Distance(dimensionFenetre tempFen1, dimensionFenetre tempFen2, string type) {
    float dist=0;
    int dro=0;
    int gau=0
    if (type=="fen") { dro=1; gau=1;}
    if (type=="dro") { dro=1;}
    if (type=="gau") { gau=1;}


    dist += gau*max(tempFen2.hautgond2g-tempFen1.hautgond2g,
                 tempFen1.hautgond2g-tempFen2.hautgond2g);
    dist+= gau*max(tempFen2.gond2basg-tempFen1.gond2basg,
                 tempFen1.gond2basg-tempFen2.gond2basg);
    dist+= gau*max(tempFen2.hautgond1g-tempFen1.hautgond1g,
                 tempFen1.hautgond1gtempFen2.hautgond1g);
    dist+= gau*max(tempFen2.gond1basg-tempFen1.gond1basg,
                 tempFen1.gond1basg-tempFen2.gond1basg);

    dist += dro*max(tempFen2.hautgond2d-tempFen1.hautgond2d,
                 tempFen1.hautgond2d-tempFen2.hautgond2d);
    dist+= dro*max(tempFen2.gond2basd-tempFen1.gond2basd,
                 tempFen1.gond2basd-tempFen2.gond2basd);
    dist+= dro*max(tempFen2.hautgond1d-tempFen1.hautgond1d,
                 tempFen1.hautgond1d-tempFen2.hautgond1d);
    dist+= dro*max(tempFen2.gond1basd-tempFen1.gond1basd,
                 tempFen1.gond1basd-tempFen2.gond1basd);

    dist=float(pow(dist,1/4));
    return (dist);

}


void Clustering() {

    dimensionFenetre test1;
    dimensionVolet test2;

    for (int i=0; i<gauches.size(); i++) {
            clGauches.push_back(test2);
            clDroits.push_back(test2);
            clFenetres.push_back(test1);
    }

    for (int i=0; i<gauches.size(); i++) {

        test2.index=gauches[i].index;
        test2.hautgond2=gauches[i].hauteurGondSommet+gauches[i].hauteurInterGonds;
        test2.gond2bas=gauches[i].hauteurTotale - gauches[i].hauteurGondSommet - gauches[i].hauteurInterGonds;
        test2.hautgond1=gauches[i].hauteurGondSommet;
        test2.gond1bas=gauches[i].hauteurTotale - gauches[i].hauteurGondSommet;
        clGauches[test2.index]=test2;


        test2.index=droits[i].index;
        test2.hautgond2=droits[i].hauteurGondSommet+droits[i].hauteurInterGonds;
        test2.gond2bas=droits[i].hauteurTotale - droits[i].hauteurGondSommet - droits[i].hauteurInterGonds;
        test2.hautgond1=droits[i].hauteurGondSommet;
        test2.gond1bas=droits[i].hauteurTotale - droits[i].hauteurGondSommet;
        clDroits[test2.index]=test2;

        test1.index=fenetres[i].index;
        test1.hautgond2g=fenetres[i].hauteurGondSommetGauche+fenetres[i].hauteurInterGondsGauche;
        test1.gond2basg=fenetres[i].hauteurTotale - fenetres[i].hauteurGondSommetGauche - fenetres[i].hauteurInterGondsGauche;
        test1.hautgond1g=fenetres[i].hauteurGondSommetGauche;
        test1.gond1basg=fenetres[i].hauteurTotale - fenetres[i].hauteurGondSommetGauche;

        test1.hautgond2d=fenetres[i].hauteurGondSommetDroit+fenetres[i].hauteurInterGondsDroit;
        test1.gond2basd=fenetres[i].hauteurTotale - fenetres[i].hauteurGondSommetDroit - fenetres[i].hauteurInterGondsDroit;
        test1.hautgond1d=fenetres[i].hauteurGondSommetDroit;
        test1.gond1basd=fenetres[i].hauteurTotale - fenetres[i].hauteurGondSommetDroit;
        clFenetress[test1.index]=test1;
    }
    float deltaCout=10;
    float Cout=100000;
    float ancienCout=150000;
    cluster clustempo;
    dimensionFenetre noyau;
    dimensionFenetre tempVolet;
    dimensionFenetre tempFenetre;
    dimensionFenetre retenuVolet;
    dimensionFenetre retenuFenetre;
    int j=0;
    float distanceMini[3];
    int indiceretenu[3]=[0,0,0];
    float disttemp;

    vector <int> indicesNonDispoDro;
    vector <int> indicesNonDispoGau;
    vector <int> indicesNonDispoFen;

    for (int i = 0; i<nombreCluster; i++) {
        clusters.push_back(clustempo);
        clusters[i].noyau=clFenetre[i];
    }

    while (deltaCout>50) {

        ancienCout=Cout;
        Cout=0;

        for( int i =0; i < fenetres.size(); i++) {
            noyau=clusters[i%nombreCluster].noyau;
            j=0
            distanceMini=[1500000,1500000,1500000]; // droit gauche fenetre
            indiceretenu=[-1,-1,-1];
            while ( j<fenetres/size()) {
                tempVolet=FusionVolet(clDroits[j], clGauches[j]);
                tempFenetre=clFenetres[j];

                disttemp=Distance(noyau,tempVolet, "dro")
                if (disttemp<distanceMini[0] and !(std::find(indicesNonDispoDro.begin(), indicesNonDispoDro.end(), j) != indicesNonDispoDro.end())) {
                    indiceretenu[0]=j;
                    distanceMini[0]=disttemp;
                }

                disttemp=Distance(noyau,tempVolet, "gau")
                if (disttemp<distanceMini[1] and !(std::find(indicesNonDispoGau.begin(), indicesNonDispoGau.end(), j) != indicesNonDispoGau.end())) {
                    indiceretenu[1]=j;
                    distanceMini[1]=disttemp;
                }

                disttemp=Distance(noyau,tempFenetre, "fen")
                if (disttemp<distanceMini[2] and !(std::find(indicesNonDispoFen.begin(), indicesNonDispoFen.end(), j) != indicesNonDispoFen.end())) {
                    indiceretenu[2]=j;
                    distanceMini[2]=disttemp;
                }


            }

            clusters[i%nombreCluster].droits.push_back(indiceretenu[0]);
            clusters[i%nombreCluster].gauches.push_back(indiceretenu[1]);
            clusters[i%nombreCluster].fenetres.push_back(indiceretenu[2]);

            indicesNonDispoDro.push_back(indiceretenu[0]);
            indicesNonDispoGau.push_back(indiceretenu[1]);
            indicesNonDispoFen.push_back(indiceretenu[2]);
            j++;
            Cout+= distanceMini[0]+distanceMini[1]+distanceMini[2];

    }
    deltaCout=ancienCout-Cout;


}


void Hongrois(string cheminz, string fenetresFile, string gauchesFile, string droitsFile) {



    readCsvToMap<Fenetre>(fenetres, fenetresFile);


    readCsvToMap<Volet>(gauches, gauchesFile);


    readCsvToMap<Volet>(droits, droitsFile);


    if fenetres.size()>tailleCluster {
            nombreCluster=int(fenetres.size()/tailleCluster);


    }

}

void matriceCout(string cheminz, string fenetresFile, string gauchesFile, string droitsFile)



#endif // HONGROIS_H
