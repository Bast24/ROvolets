#pragma once
#include "ressource.h"

/// Constantes
const float T0 = 2.0;
const float Tmin = 1e-3;
const float tau = 1e5;
const float a = 0.0001;
const float beta = 0.999999;

void InitRandom();

/// Recuit simulé
void Fluctuation(MapSolutions & current_sol, int i, int j, int obj);
bool Metropolis(const float T, const float dE);
void Recuit(MapSolutions & current_sol, MapFenetres const & fenetres, MapVolets const & gauches, MapVolets const & droits, bool verbose);
