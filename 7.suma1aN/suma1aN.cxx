///
/// suma1aN.cxx
///
/// Ejercicio de evaluación
///
/// calcular suma(i = 1 .. N, i) donde N es pasado como argumento
///

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, const char *argv[])
{
  /// ...
  /// Tip: consideren suma1a10 y de1aN
  /// ...
  int N =stoi(argv[1]);
  int resultado = 0;
  int i=1;
  int sumaNotable=(N*(N+1))/2;
  while (i <= N) {
    resultado=resultado+i;
    i = i + 1;
    if (sumaNotable==resultado) {
      fprintf(stdout, "se cumple que suma(i=1,2,...N ,i)==(N*(N+1))/2\n");
    }
  }
  fprintf(stdout, "La suma de 1 a %d == %d\n", N, resultado);
  return 0;
}
