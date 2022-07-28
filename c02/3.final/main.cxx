///
/// main.cxx
///
/// Tarea Final: programa principal
///

#include "test_dyna.h"
#include "test_matrix.h"
#include "test_table.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Este codigo, y el de todos los archivos test_*, se provee como esqueleto
/// Deben seguir el esqueleto y extenderlo: estas prueba no son suficientes
/// - no prueban todas las funciones, mucho menos combinaciones de las mismas
/// - no cubren usos tipicas y atipicos de las funciones
/// - no consideran casos de borde, casos perversos, etc.
///
/// 20% de la evaluacion de esta tarea (10 puntos) se basa en:
/// - buena cobertura: completitud y probabilidad de pillar errores
/// - calidad del codigo de prueba: modularidad, claridad, limpieza, etc.
/// - eficiencia: esencialmente evitar pruebas que no mejoran la cobertura
///
/// Son buenos ingenieros: investiguen!
/// https://en.wikipedia.org/wiki/Code_coverage
/// https://en.wikipedia.org/wiki/Software_testing
/// https://en.wikipedia.org/wiki/Edge_case

static int dispatch(int argc, const char *argv[]) {
  if (strcmp(argv[1], "dyna") == 0) {
    return test_dynamic_arrays(argc, argv);
  }
  if (strcmp(argv[1], "matrix") == 0) {
    return test_matrix(argc, argv);
  }
  if (strcmp(argv[1], "table") == 0) {
    return test_table(argc, argv);
  }
}

///
/// Main: punto de entrada
///
int main(int argc, const char *argv[]) {
  // acceptar no menos de un argumento para despachar
  assert(2 <= argc);
  int status = dispatch(argc, argv);
  if (status != 0) {
    fprintf(stderr, "se completo con errores: status %d\n", status);
  }
  return status;
}
