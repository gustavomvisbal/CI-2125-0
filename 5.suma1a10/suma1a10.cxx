///
/// suma1a10.cxx
///
/// Ejercicio: calcular suma(i = 1 .. 10, i)
///

#include <stdio.h>

int main()
{
  int resultado = 0;
  int i=1;
  // ... sumar cada i al resultado
  while (i <= 10) {
    resultado=resultado+i;
    i = i + 1;
  }
  fprintf(stdout, "suma(i = 1 .. 10, i) == %d\n", resultado);
  return 0;
}
