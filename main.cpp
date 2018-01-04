
#include <iostream>
#include <ctime>

#include "SharedElements.h"
#include "ressources.h"
#include "recuit.h"





string instance= "moyenneFaisable";
string chemin = "instances/";
string wd = "C:/Users/pierr/Documents/0ENPC/01A/INFO/stock/RECHOPPE/";







//////////////////////////////////////////////////////
//MAIN
//////////////////////////////////////////////////////

int main()
{
    InitRandom();
    chemin = wd+chemin;

    string fenetresFile = chemin+instance+"_fenetres.csv";
    string gauchesFile = chemin+instance+"_voletsDroits.csv";
    string droitsFile = chemin+instance+"_voletsGauches.csv";
    string solutionsFile = chemin+instance+"_sol.csv";
    bool verbose = false;


/*
    map<int,int> fenetres = readWidthFile(fenetresFile);
    map<int,int> voletsGauches = readWidthFile(gauchesFile);
    map<int,int> voletsDroits = readWidthFile(droitsFile);*/
    map<int,FenetreAvecVolet> solutions;
    //readCsvToMap(solutions, solutionsFile);
    //cout << solutions.size();
    recuit(solutionsFile, fenetresFile, gauchesFile, droitsFile);



    //readCsvToMap<FenetreAvecVolet>(solutions, solutionsFile);


    return(evaluateSolution(solutions, fenetres, gauches, droits, false));
}
