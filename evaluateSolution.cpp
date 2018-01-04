#include "recuit.h"

string instance= "versaillesOpt";
string instChemin = "instances/";
string solChemin = "solutions/";
string wd = "C:/Users/basti/Documents/C++/ROvolets/";

string fenetresFile = wd + instChemin + instance + "_fenetres.csv";
string gauchesFile = wd + instChemin + instance + "_voletsGauches.csv";
string droitsFile = wd + instChemin + instance + "_voletsDroits.csv";
string solutionsFile = wd + solChemin + instance + "_sol.csv";



int main(){

    InitRandom();

    MapFenetres fenetres;
    readCsvToMap<Fenetre>(fenetres, fenetresFile);

    MapVolets gauches;
    readCsvToMap<Volet>(gauches, gauchesFile);

    MapVolets droits;
    readCsvToMap<Volet>(droits, droitsFile);

    int size = droits.size();
    bool verbose = false;

    MapSolutions solutions;
    genereSolutionAlea(solutions, size);
    int nbBloquages_old = evaluateSolution(solutions, fenetres, gauches, droits, verbose);
    cout << nbBloquages_old << endl;



    Recuit(solutions, fenetres, gauches, droits, verbose);

    int nbBloquages_new = evaluateSolution(solutions, fenetres, gauches, droits, verbose);
    cout << nbBloquages_new << endl;


	return 0;
}
