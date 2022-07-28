///
/// init.cxx
///

#include "init.h"
#include "stochastic.h"

#include <stdio.h>
#include <string.h>

// pueden agregar mas funciones si lo desean, no hay problema
// (considero que  estas son mas que suficientes para hacer pruebas)
// pero mantengan compatibilidad: no cambien las existentes y sus codigos

static double zero(int) {
  return 0.0;
}

static double fortytwo(int) {
  return 42.0;
}

static double index(int i) {
  return double(i);
}

static double u(int) {
  return uniform();
}

static double z(int) {
  return normal();
}

static double fancy(int i) {
  return i + uniform();
}

// return array initializer function given the user choice
// valid initializer choices are: "0", "42", "u", and "f"
Initializer get_initializer(const char *choice) {
  if (strcmp(choice, "0") == 0) {
    return zero;
  }
  if (strcmp(choice, "42") == 0) {
    return fortytwo;
  }
  if (strcmp(choice, "i") == 0) {
    return index;
  }
  if (strcmp(choice, "u") == 0) {
    return u;
  }
  if (strcmp(choice, "z") == 0) {
    return z;
  }
  if (strcmp(choice, "f") == 0) {
    return fancy;
  }
  // reportar error y seguir
  fprintf(stderr, "advertencia: seleccion invalida - usando la funcion 'zero'\n");
  return zero;
}
