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
#include <string.h>

// largo de los nombres, medido contando!
const int N = 9;

// animalitos de la casa: mascotas
char canary_a[] = { 'C', 'a', 'n', 'a', 'r', 'i', 'o', ' ', 'A' };
char anaconda[] = { 'A', 'n', 'a', 'c', 'o', 'n', 'd', 'a', '!' };
char canary_b[] = { 'C', 'a', 'n', 'a', 'r', 'i', 'o', ' ', 'B' };

const char *pets[] = { canary_a, anaconda, canary_b };

/// mostrar sub-rango de un arreglo de caracteres
/// int lb: limite inferior del rango
/// int ub: limite superior del rango (no incluido)
/// const char s[]: los animalitos de la casa
/// precondition 0 <= lb < ub <= N
void show_string_range(int lb, int ub, const char s[]) {
  for (int i = lb; i < ub; ++i) {
    fprintf(stdout, "%c", s[i]);
  }
}

/// mostrar mascota
/// const char *pet: nombre
/// precondition: pet has exactly N characters
void show_pet(const char *pet) {
  show_string_range(0, N, pet);
}

/// mostrar las mascotas
/// int n: numero de animalitos de la casa
/// const char *pets[]: arreglo con los animalitos de la casa
void show_pets(int n, const char *pets[]) {
  for (int i = 0; i < n; ++i) {
    fprintf(stdout, "pets[%d]: ", i);
    show_pet(pets[i]);
    fprintf(stdout, "\n");
  }
}

int main(int argc, const char *argv[])
{
  fprintf(stdout, "canary a: %2d characters\n", strlen(canary_a));
  fprintf(stdout, "anaconda: %2d characters\n", strlen(anaconda));
  fprintf(stdout, "canary b: %2d characters\n", strlen(canary_b));
  fprintf(stdout, "........\n");

  int NP = sizeof(pets) / sizeof(pets[0]);
  show_pets(NP, pets);
  fprintf(stdout, "........\n");

  assert(argc <= 2);

  int k = (argc == 1 ? 0 : atoi(argv[1]));
  fprintf(stdout, "pets[%d]: %s\n", k, pets[k]);
  return 0;
}
