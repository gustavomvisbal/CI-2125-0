///
/// de1a10.cxx
///
/// Programa de ejemplo que cuenta 1 a 10
/// Muestra el uso de la instrucción while para iterar
///

#include <stdio.h>

int main()
{
  int i = 1;
  while (i <= 10) {
    fprintf(stdout, "Numero: %d\n", i);
    i = i + 1;
  }
}

// Ejercicio: definir una constante entera N para el numero 10
