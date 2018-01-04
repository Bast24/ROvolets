#pragma once


#include "SharedElements.h"

typedef map<int, Fenetre> MapFenetres;
typedef map <int, Volet> MapVolets;
typedef map<int, FenetreAvecVolet> MapSolutions;

void genereSolutionAlea(MapSolutions & solutions, int longueur);

int nbRabotsFenetre(FenetreAvecVolet const & solution, MapFenetres const & fenetres, MapVolets const & gauches, MapVolets const & droits, bool verbose);

int evaluateSolution(MapSolutions const & solutions, MapFenetres const & fenetres, MapVolets const & gauches, MapVolets const & droits, bool verbose);
