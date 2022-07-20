///
/// The Art of Living Dangerously
/// what can happen when entering undefined behavior territory
///
/// El Arte de Vivir de Manera arriesgada
/// probando peligrosamente lo que pasa al "violar" los limites
///

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

const int N = 8;

/// mostrar sub-rango de un arreglo de numeros (doble precision)
/// int lb: limite inferior del rango
/// int ub: limite superior del rango (no incluido)
/// const double a[]: arreglo de numeros
/// precondicion 0 <= lb < ub <= length(a)
void show(int lb, int ub, const double a[]) {
  fprintf(stdout, "[\n");    
  for (int i = lb; i < ub; ++i) {
    fprintf(stdout, "  %2d -> %f\n", i, a[i]);    
  }
  fprintf(stdout, "]\n");    
}

/// inicializar arreglo de numeros (doble precision)
/// int v: valor inicial para todos los elementos en el rango
/// int lb: limite inferior del rango
/// int ub: limite superior del rango (no incluido)
/// double a[]: arreglo de numeros
void assign_range(double v, int lb, int ub, double a[]) {
  for (int i = lb; i < ub; ++i) {
    a[i] = v;
  }
}

/// probar peligrosamente lo que pasa al "violar" los limites
/// int n: (supuesto) tamano del arreglo
/// const double a[]: arreglo de numeros
void test(int lb, int ub, double a[]) {
  fprintf(stdout, "antes (rango): ");
  show(lb, ub, a);
  fprintf(stdout, "antes (0 - N): ");
  show(0, N, a);
  assign_range(42.0, lb, ub, a);
  fprintf(stdout, "despues (rango): ");
  show(lb, ub, a);
  fprintf(stdout, "despues (0 - N): ");
  show(0, N, a);
}

int main_test(int argc, const char *argv[])
{
  double canary_a[] = { 1.1, 1.1, 1.1, 1.1, 1.1, 1.1, 1.1, 1.1 };
  double x[N];
  double canary_b[] = { 8.8, 8.8, 8.8, 8.8, 8.8, 8.8, 8.8, 8.8 }; 

  // parse arguments (minimal checking)
  assert(argc == 3);
  int lower = atoi(argv[1]);
  int upper = atoi(argv[2]);

  // push the envelope
  test(lower, upper, x);

  // check "canaries" and exit
  fprintf(stdout, "Canario A: ");
  show(0, 8, canary_a);
  fprintf(stdout, "Canario B: ");
  show(0, 8, canary_b);

  return 0;
}

int main(int argc, const char *argv[])
{
  return main_test(argc, argv);
}
