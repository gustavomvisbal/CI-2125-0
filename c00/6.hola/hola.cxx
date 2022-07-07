///
/// hola.cxx
///
/// Ejercicio: completar el programa
///

#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
  if (argc == 1) {
    // ... imprimir "Hola!"
    fprintf(stdout, "Hola!\n");
    return 0;
  } else if (argc == 2) {
    // ... imprimir "Hola <nombre>!"
    fprintf(stdout, "Hola, %s!", argv[1]);
  } else {
    fprintf(stderr, "uso: %s [<nombre>]\n", argv[0]);
    return 1;
  }
  return 0;
}
