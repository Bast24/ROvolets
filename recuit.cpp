#include "recuit.h"
#include <cassert>

void InitRandom() {
    srand((unsigned int)time(0));
}

void Fluctuation(MapSolutions & current_sol, int i, int j, int obj) {
    assert(obj < 3 && obj >= 0 );
    if (obj == 0) {
        int temp = current_sol[j].indexFenetre;
        current_sol[j].indexFenetre = current_sol[i].indexFenetre;
        current_sol[i].indexFenetre = temp;
    }
    else if (obj == 1) {
        int temp = current_sol[j].indexVoletGauche;
        current_sol[j].indexVoletGauche = current_sol[i].indexVoletGauche;
        current_sol[i].indexVoletGauche = temp;

    }
    else {
        int temp = current_sol[j].indexVoletDroit;
        current_sol[j].indexVoletDroit = current_sol[i].indexVoletDroit;
        current_sol[i].indexVoletDroit = temp;
    }
}


bool Metropolis(const float T, const float dE) {
    return (float(rand())/RAND_MAX < exp(-dE / T));
}


void Recuit(MapSolutions & current_sol, MapFenetres const & fenetres, MapVolets const & gauches, MapVolets const & droits, bool verbose) {
    int compt = 0;
    float T = T0;
    int size = current_sol.size();
    // Energie que l'on cherche à minimiser (pour l'instant le nb de coups de rabots)
    float E = evaluateSolution(current_sol, fenetres, gauches, droits, verbose);
    float dE;
    // Indices que l'on choisit pour la fluctuation
    int i = rand()%size ; int j = rand()%size;
    int obj = rand()%3;

    while (T > Tmin) {
        if (i != j) {
            // On stocke le nb de coups de rabots qui concernent seulement les volets/fenetres affectés par la fluctuation (pour ne pas tout recalculer)
            int rabot_temp = nbRabotsFenetre(current_sol[i], fenetres, gauches, droits, verbose) + nbRabotsFenetre(current_sol[j], fenetres, gauches, droits, verbose);
            // On applique la fluctuation
            Fluctuation(current_sol,i,j,obj);
            // On recalcule l'énergie
            dE = - rabot_temp + nbRabotsFenetre(current_sol[i], fenetres, gauches, droits, verbose) + nbRabotsFenetre(current_sol[j], fenetres, gauches, droits, verbose);
            // On applique l'algo de metropolis : si il renvoie true --> On change au nouvel état
            if (Metropolis(T,dE)) {
                E = E + dE;
            }
            // Sinon, on réapplique la fluctuation (transposition)
            else
                Fluctuation(current_sol, i, j, obj);
            // Loi de décroissance de la température
            T = T * beta;
            //T = T0/(1+a*compt);
            //T = T0/log(2+compt); // surtout pas !

            compt ++;
            if (compt%10000 == 0) {
                cout << "Coups de rabots : " << E << endl;
                cout << "Temperature : " << T << endl;
            }
        }
        i = rand()%size; j = rand()%size;
        obj = rand()%3;
    }
}
