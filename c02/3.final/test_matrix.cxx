///
/// Pruebas de matrices: funcionales y de rendimiento
///
/// deben ser extendidas
///

#include "test_matrix.h"
#include "init.h"
#include "matrix.h"

#include <assert.h>
#include <stdio.h>

/// show_matrix: imprime una matrix
///
/// const char *name: nombre o etiqueta para identificar la matriz
/// const Matrix *: apuntador a la matriz
static void show_matrix(const char *name, const Matrix *matrix) {
  // no podemos acceder directamente a los campos de la estructura Matrix ...
  // ... y tampoco cambiarlos, ya que son partes privadas de la implementacion.
  // pero podemos obtener sus valores usando las funciones de acceso
  size_t NR = matrix_nr(matrix);
  size_t NC = matrix_nc(matrix);
  const double **data = matrix_data(matrix);

  fprintf(stdout, "%s: forma: (%zux%zu)\n", name, NR, NC);
  fprintf(stdout, "[\n");
  for (size_t i = 0; i < NR; ++i) {
    fprintf(stdout, "\t[");
    for (size_t j = 0; j < NC; ++j) {
      fprintf(stdout, " %12.6f", data[i][j]);
    }
    fprintf(stdout, " ]\n");
  }
  fprintf(stdout, "]\n\n");
}

static int test_matrix_quick() {
  Initializer fortytwo = get_initializer("42");
  Initializer uniform =  get_initializer("u");
  Initializer normal =  get_initializer("z");

  Matrix *m42 = matrix(4, 8, fortytwo);
  show_matrix("m42", m42);

  Matrix *mxu = matrix(6, 8, uniform);
  show_matrix("mxu", mxu);

  Matrix *mxz = matrix(8, 8, normal);
  show_matrix("mxz", mxz);

  // "probar" (parcialmente) la liberacion de memoria

  matrix_destroy(&m42);
  matrix_destroy(&mxu);
  matrix_destroy(&mxz);

  assert(m42 == nullptr);
  assert(mxu == nullptr);
  assert(mxz == nullptr);

  // ... mas pruebas, a su juicio

  return 0;
}

/// prueba la suma de matrices
static int test_matrix_sum(int M, int N) {
  Initializer sequence = get_initializer("i");
  Initializer uniform =  get_initializer("u");

  Matrix *lhs = matrix(M, N, sequence);
  show_matrix("lhs", lhs);

  Matrix *rhs = matrix(M, N, uniform);
  show_matrix("rhs", rhs);

  Matrix *sum = matrix_sum(lhs, rhs);
  assert(sum != nullptr); // siempre es una buena idea chequear que no hubo error
  show_matrix("sum", sum);

  matrix_destroy(&sum);
  assert(sum == nullptr);

  Matrix *bad = matrix(M, N+1, uniform);
  sum = matrix_sum(lhs, bad); // 
  assert(sum == nullptr); // aqui de hecho *experamos* un error
  // show_matrix("sum", sum); // ¿que pasa si tratan de ver la matriz?

  // ... mas pruebas, a su juicio

  return 0;
}

/// prueba la multiplicacion de matrices
static int test_matrix_mult(int M, int N, int K) {
  // ...
  // como deben imaginarse, deben crear una matrix lhs (MxN) y una matriz rhs (NxK)
  // y una matriz res (MxK) correspondiente a lhs * rhs (multiplicacion de matrices)
  // https://en.wikipedia.org/wiki/Matrix_multiplication
  // muestren las 3 matrices en pantalla
  //
  // repetir lo anterior unas tres veces
  // consideren casos especiales que facilitan verificar el resultado
  // ...
  return 0;
}

int test_matrix(int argc, const char *argv[]) {
  if (argc == 2) {
    return test_matrix_quick();  
  }

  if (argc == 4) {
    int M = atoi(argv[2]);
    int N = atoi(argv[3]);
    return test_matrix_sum(M, N);
  }

  if (argc == 5) {
    int M = atoi(argv[2]);
    int N = atoi(argv[3]);
    int K = atoi(argv[4]);
    return test_matrix_mult(M, N, K);  
  }

  return -1;
}
