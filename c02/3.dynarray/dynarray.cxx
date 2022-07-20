///
/// dynamic array operations
///

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  double *data;
  size_t size;
  size_t capacity;
} Dynarray;

typedef double (*Initializer)(int i);

Dynarray dynarray(int N, Initializer init) {
  Dynarray result;
  result.data = (double *) malloc(N * sizeof(double));
  for (int i = 0; i < N; ++i) {
    result.data[i] = init(i);
  }
  result.size = result.capacity = N;
  return result;
}

/// computa el promedio de los valores en el arreglo x
/// n: tamano del arreglo
/// x: arreglo de datos
double mean(const Dynarray *dar) {
  double sum = 0.0;
  for (int i = 0; i < dar->size; ++i) {
    sum += dar->data[i];
  }
  const double result = sum / dar->size;
  return result;
}

/// computa la varianza de los valores en el arreglo x
/// utiliza la formula computacional para mejorar la eficiencia
/// n: tamano del arreglo
/// x: arreglo de datos
static double varp_ecf(const Dynarray *dar) {
  double sx = 0.0;
  double sx2 = 0.0;
  for (int i = 0; i < dar->size; ++i) {
    double xi = dar->data[i];
    sx += xi;
    sx2 += xi * xi;
  }
  const double mean = sx / dar->size;
  const double result = sx2 / dar->size - mean * mean;
  return result;
}


void show_dynarray(const Dynarray *dyna) {
  size_t N = dyna->size;
  fprintf(stdout, "[\n");
  for (size_t i = 0; i < N; ++i) {
    fprintf(stdout, "  %8.6f\n", dyna->data[i]);
  }
  fprintf(stdout, "]\n");
}

Dynarray concatenate(const Dynarray *lhs, const Dynarray *rhs) {
  Dynarray result;
  size_t M = lhs->size;
  size_t N = rhs->size;

  result.size = result.capacity = 0; // ... completar

  result.data = (double *) malloc(result.capacity * sizeof(double));

  // ... completar

  return result;
}

// Initializer functions

double fortytwo(int) {
  return 42;
}

double uniform(int) {
  return double(rand()) / double(RAND_MAX);
}

double fancy(int i) {
  return i + uniform(i);
}

// Main

int main(int argc, const char *argv[]) {
  assert(argc == 3);
  const int M = atoi(argv[1]);
  const int N = atoi(argv[2]);

  Dynarray x = dynarray(M, fancy);
  show_dynarray(&x);

  Dynarray y = dynarray(N, fancy);
  show_dynarray(&y);

  Dynarray z = dynarray(1024, uniform);
  double avg = mean(&z);
  double var = varp_ecf(&z);
  fprintf(stdout, "avg = %f, var = %f\n", avg, var);

  Dynarray result = concatenate(&x, &y);
  show_dynarray(&result);
}
