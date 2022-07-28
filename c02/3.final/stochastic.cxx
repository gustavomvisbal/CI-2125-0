///
/// stochastic.cxx
///

#include "stochastic.h"

#include <math.h>

/// semilla inicial por defecto
static double seed = 0.1415926539;

/// cambia la semilla de generacion de numeros aleatorios
/// retorna el valor de la semilla anterior
double reset_seed(double new_seed) {
  double old_seed = seed;
  seed = new_seed;
  return old_seed;
}

/// genera un numero aleatorio entre 0 y 1
double uniform() {
  double w = 997 * seed;
  seed = w - floor(w);
  return seed;
}

/// genera un numero aleatorio de acuerdo a una distribucion normal estandar
/// la distribucion normal estandar tiene promedio 0 y varianza 1
double normal() {
  double result = sqrt(-2 * log(uniform())) * cos(2 * M_PI * uniform());
  return result;
}

/// genera un entero aleatorio k tal que lb <= k < ub
int random_int(int lb, int ub) {
  int k = lb + int(floor((ub - lb) * uniform()));
  return k;
}
