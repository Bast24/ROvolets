#include "ressource.h"

void genereSolutionAlea(MapSolutions & solutions, const int size) {
    vector<int> indexFenetres ;
    vector<int> indexDroits ;
    vector<int> indexGauches ;

    for (int i =0; i<size; i++) {
        indexDroits.push_back(i);
        indexGauches.push_back(i);
        indexFenetres.push_back(i);
    }
    int ifen;
    int igau;
    int idro;
    int temp;
    FenetreAvecVolet tempo;


    for (int k =0; k<size; k++) {
        ifen= (rand()*(size-k-1))/RAND_MAX;
        igau= (rand()*(size-k-1))/RAND_MAX;
        idro= (rand()*(size-k-1))/RAND_MAX;

        temp= indexDroits[idro];
        indexDroits[idro]=indexDroits.back();
        indexDroits.pop_back();
        tempo.indexVoletDroit=temp;

        temp= indexGauches[igau];
        indexGauches[igau]=indexGauches.back();
        indexGauches.pop_back();
        tempo.indexVoletGauche=temp;

        temp= indexFenetres[ifen];
        indexFenetres[ifen]=indexFenetres.back();
        indexFenetres.pop_back();
        tempo.indexFenetre=temp;


        solutions.insert(pair<int,FenetreAvecVolet> (solutions.size(), tempo) );
    }

}

int nbRabotsFenetre(FenetreAvecVolet const & solution, MapFenetres const & fenetres, MapVolets const & gauches, MapVolets const & droits, bool verbose){
    int result = 0;
    Fenetre fenetre = fenetres.find(solution.indexFenetre)->second;
    Volet gauche = gauches.find(solution.indexVoletGauche)->second;
    Volet droit = droits.find(solution.indexVoletDroit)->second;

    if (verbose) cout << "F:" << solution.indexFenetre << " G:" << solution.indexVoletGauche << " D:" << solution.indexVoletDroit << ", " ;

    //bloque en haut à gauche
    if (gauche.hauteurGondSommet > fenetre.hauteurGondSommetGauche ||
            gauche.hauteurInterGonds + gauche.hauteurGondSommet > fenetre.hauteurInterGondsGauche + fenetre.hauteurGondSommetGauche){
        ++result;
        if (verbose) cout << " bloque haut gauche," ;
    }

    //bloque en bas à gauche
    if (gauche.hauteurTotale - gauche.hauteurGondSommet > fenetre.hauteurTotale - fenetre.hauteurGondSommetGauche &&
            gauche.hauteurTotale - gauche.hauteurGondSommet - gauche.hauteurInterGonds >
                fenetre.hauteurTotale - fenetre.hauteurGondSommetGauche - fenetre.hauteurInterGondsGauche){
        ++result;
        if (verbose) cout << " bloque bas gauche,";
    }

    //bloque en haut à droit
    if (droit.hauteurGondSommet > fenetre.hauteurGondSommetDroite ||
            droit.hauteurInterGonds + droit.hauteurGondSommet > fenetre.hauteurInterGondsDroite + fenetre.hauteurGondSommetDroite ){
        ++result;
        if (verbose) cout << " bloque haut droit,";
    }

    //bloque en bas à droit
    if (droit.hauteurTotale - droit.hauteurGondSommet > fenetre.hauteurTotale - fenetre.hauteurGondSommetDroite &&
            droit.hauteurTotale - droit.hauteurGondSommet - droit.hauteurInterGonds >
                fenetre.hauteurTotale - fenetre.hauteurGondSommetDroite - fenetre.hauteurInterGondsDroite){
        ++result;
        if (verbose) cout << " bloque bas droit,";
    }
    // bloque au centre
    if (gauche.largeur + droit.largeur > fenetre.largeurTotale)
    {
        ++result;
        if (verbose) cout << "bloque centre,";
    }
    if (verbose) cout << endl;
    return result;
}


int evaluateSolution(MapSolutions const & solutions, MapFenetres const & fenetres, MapVolets const & gauches, MapVolets const & droits, bool verbose){
    int result = 0;
    for (typename MapSolutions::const_iterator it = solutions.begin(); it!= solutions.end(); ++it){
        result += nbRabotsFenetre(it->second, fenetres, gauches, droits, verbose);
    }
    return result;
}
