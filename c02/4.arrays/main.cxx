///
/// programa de prueba
///

#include "arrayops.h"
#include "statistics.h"
#include "stochastic.h"

#include <stdio.h>

//
// WILD, WILD, WEST RULES IN EFFECT FROM HERE TO THE END!
// ======================================================
//
// Significa que pueden cambiar todo lo que les de la gana
// Pero van a ser evaluados en lo que hagan aqui
// 
// - Claridad del codigo ~50%
// - Completitud de la cobertura ~40%
// - Eficiencia de la cobertura  ~10%
//

// data para hacer pruebas (some data to play around)

// empty array of double
const int N0 = 0;
double *e0 = 0;

// 1 double
double a1[] = { 0.0 };
const int N1 = sizeof(a1) / sizeof(a1[0]);

// 8 ints
int a8[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
const int N8 = sizeof(a8) / sizeof(a8[0]);

// 1 kilo int
const int NI = 1024;
int *ai = int_array(NI);

// 1 kilo double
const int NK = 1024;
double *ak = random_uniform_array(NK);

// 1 mega double
const int NM = 1024 * 1024;
double *am = random_uniform_array(NM);

// 8 strings
const char *as[] = { "Alpha", "Beta", "Charlie", "Delta", "Echo", "Fox", "Golf", "Hotel" };
const int NS = sizeof(as) / sizeof(as[0]);

// 64 strings (idea: combinar 8 nombres con 8 apellidos => 64 nombres completos)
const int NN = 64;
const char **an = string_array(NN);

void init() {
  // aqui "re-inicializamos" 'ai' para tener data mas "interesante" que puros ceros
  for (int i = 0; i < NI; ++i) {
    ai[i] = i;
  }

  // este puede ser un lugar adecuado para inicializar an, de ser necesario
}

// funciones para mostrar arreglos

const int MAX = 8;

void show_int_array(const char *name, int n, const int x[]) {
  fprintf(stdout, "<<< %s >>>\n", name);
  if (n <= MAX) {
    for (int i = 0; i < n; ++i) {
      fprintf(stdout, "%s[%d]: %d\n", name, i, x[i]);
    }
  } else {
    for (int i = 0; i < MAX/2; ++i) {
      fprintf(stdout, "%s[%d]: %d\n", name, i, x[i]);
    }
    fprintf(stdout, "...\n");
    for (int i = n - MAX/2; i < n; ++i) {
      fprintf(stdout, "%s[%d]: %d\n", name, i, x[i]);
    }
  }
}

void show_double_array(const char *name, int n, const double x[]) {
  fprintf(stdout, "<<< %s >>>\n", name);
  if (n <= MAX) {
    for (int i = 0; i < n; ++i) {
      fprintf(stdout, "%s[%d]: %lf\n", name, i, x[i]);
    }
  } else {
    for (int i = 0; i < MAX/2; ++i) {
      fprintf(stdout, "%s[%d]: %lf\n", name, i, x[i]);
    }
    fprintf(stdout, "...\n");
    for (int i = n - MAX/2; i < n; ++i) {
      fprintf(stdout, "%s[%d]: %lf\n", name, i, x[i]);
    }
  }
}

void show_string_array(const char *name, int n, const char *const x[]) {
  fprintf(stdout, "<<< %s >>>\n", name);
  if (n <= MAX) {
    for (int i = 0; i < n; ++i) {
      fprintf(stdout, "%s[%d]: %s\n", name, i, x[i]);
    }
  } else {
    for (int i = 0; i < MAX/2; ++i) {
      fprintf(stdout, "%s[%d]: %s\n", name, i, x[i]);
    }
    fprintf(stdout, "...\n");
    for (int i = n - MAX/2; i < n; ++i) {
      fprintf(stdout, "%s[%d]: %s\n", name, i, x[i]);
    }
  }
}

// funciones de prueba

// prueba las funciones estadisticas
void test_stats() {

  fprintf(stdout, "Estadisticas ...\n");

  show_double_array("a1", N1, a1);
  fprintf(stdout, "\n");
  fprintf(stdout, "promedio(a1) = %lf\n", mean(N1, a1));
  fprintf(stdout, "varianza(a1) = %lf\n", varp(N1, a1));
  fprintf(stdout, "\n");

  show_double_array("ak", NK, ak);
  fprintf(stdout, "\n");
  fprintf(stdout, "promedio(data) = %lf\n", mean(NK, ak));
  fprintf(stdout, "varianza(data) = %lf\n", varp(NK, ak));
  fprintf(stdout, "\n");

  show_double_array("am", NM, am);
  fprintf(stdout, "\n");
  fprintf(stdout, "promedio(data) = %lf\n", mean(NM, am));
  fprintf(stdout, "varianza(data) = %lf\n", varp(NM, am));
  fprintf(stdout, "\n");
}

// prueba las funciones de busqueda
void test_find() {

  fprintf(stdout, "Busqueda ...\n");

  // a8
  show_int_array("a8", N8, a8);

  for (int i = -1; i <= N8; ++i) {
    int k = find_int(i, N8, a8);
    fprintf(stdout, "%d => %d\n", i, k);
  }

  shuffle_int_array(N8, a8);

  for (int i = -1; i <= N8; ++i) {
    int k = find_int(i, N8, a8);
    fprintf(stdout, "%d => %d\n", i, k);
  }

  // ai

  show_int_array("ai", NI, ai);

  for (int i = -1; i < MAX/2; ++i) {
    int k = find_int(i, NI, ai);
    fprintf(stdout, "%d => %d\n", i, k);
  }

  for (int i = NI - MAX/2; i <= NI; ++i) {
    int k = find_int(i, NI, ai);
    fprintf(stdout, "%d => %d\n", i, k);
  }

  shuffle_int_array(NI, ai);

  for (int i = -1; i < MAX/2; ++i) {
    int k = find_int(i, NI, ai);
    fprintf(stdout, "%d => %d\n", i, k);
  }

  for (int i = NI - MAX/2; i <= NI; ++i) {
    int k = find_int(i, NI, ai);
    fprintf(stdout, "%d => %d\n", i, k);
  }
}

// prueba las funciones de desordenamiento
void test_shuffle() {
  fprintf(stdout, "Desordenamiento ...\n");

  // empty
  show_double_array("e0", N0, e0);
  shuffle_double_array(N0, e0);
  show_double_array("e0", N0, e0);

  // a1
  show_double_array("a1", N1, a1);
  shuffle_double_array(N1, a1);
  show_double_array("a1", N1, a1);

  // a8
  show_int_array("a8", N8, a8);
  shuffle_int_array(N8, a8);
  show_int_array("a8", N8, a8);

  // am
  show_double_array("am", NM, am);
  shuffle_double_array(NM, am);
  show_double_array("am", NM, am);

  // as
  show_string_array("as", NS, as);
  shuffle_string_array(NS, as);
  show_string_array("as", NS, as);
}

// prueba las funciones de ordenamientodesordenamiento
void test_sort() {

  fprintf(stdout, "Ordenamiento ...\n");

  // empty
  show_double_array("e0", N0, e0);
  shuffle_double_array(N0, e0);
  show_double_array("e0", N0, e0);
  selection_sort_double_array(N0, e0);
  show_double_array("e0", N0, e0);

  // a1
  show_double_array("a1", N1, a1);
  shuffle_double_array(N1, a1);
  show_double_array("a1", N1, a1);
  selection_sort_double_array(N1, a1);
  show_double_array("a1", N1, a1);

  // a8
  show_int_array("a8", N8, a8);
  shuffle_int_array(N8, a8);
  show_int_array("a8", N8, a8);
  selection_sort_int_array(N8, a8);
  show_int_array("a8", N8, a8);

  // ai
  show_int_array("ai", NI, ai);
  shuffle_int_array(NI, ai);
  show_int_array("ai", NI, ai);
  selection_sort_int_array(NI, ai);
  show_int_array("ai", NI, ai);

  // ak
  show_double_array("ak", NK, ak);
  shuffle_double_array(NK, ak);
  show_double_array("ak", NK, ak);
  selection_sort_double_array(NK, ak);
  show_double_array("ak", NK, ak);

  /*
    desaconsejable:
    pueden intentar correrlo en la noche, a riesgo de recalentar la maquina
    necesitamos un algoritmo O(n * log(n)) para correr esto en tiempo razonable

  // am
  show_double_array("am", NM, am);
  shuffle_double_array(NM, am);
  show_double_array("am", NM, am);
  selection_sort_double_array(NM, am);
  show_double_array("am", NM, am);
  */

  // as
  show_string_array("as", NS, as);
  shuffle_string_array(NS, as);
  show_string_array("as", NS, as);
  selection_sort_string_array(NS, as);
  show_string_array("as", NS, as);

  fprintf(stdout, "\n");
}

void final_cleanup() {
  delete_array(ai);
  delete_array(ak);
  delete_array(am);
  delete_array(an);
}

// punto de arranque de las pruebas
int mosca()
{
  init();

  test_stats();
  test_find();
  test_shuffle();
  test_sort();

  final_cleanup();

  return 0;
}


const int M = 2;
const int N = 3;

void init(int a[][N])
{
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j) {
      a[i][j] = 10 * i + j;
    }
  }
}

void show(int a[][3])
{
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j) {
      fprintf(stdout, "a[%1d][%1d] = %2d\n", i, j, a[i][j]);
    }
  }
  fprintf(stdout, "\n");
}

int main(void)
{
  int a[2][3] = {0};
  // init(a);
  show(a);
  a[0][1] = 1;
  show(a);
  a[1][1] = 11;
  a[1][2] = 12;
  show(a);
  return 0;
}
