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

  Matrix *zxm = matrix(8, 8, uniform);
  show_matrix("zxm", zxm);

  Matrix *sum = matrix_sum(mxz, zxm);
  show_matrix("sum", sum);

  Matrix *mult = matrix_mult(m42, zxm);
  show_matrix("mult", mult);

  //Es posible realizar una operación sobre el resultado de otra siempre y cuando se cumplan ue después de realizar la primera
  //operació, se cumplan las condiciones para realizar la segunda
  Matrix *mult_sum = matrix_mult (sum, zxm);
  show_matrix ("sum por uno de los sumandos", mult_sum);

  Matrix *no_conmuta = matrix_mult(zxm, mxu);

  Matrix *incons_sum = matrix_sum(zxm, m42);

  // "probar" (parcialmente) la liberacion de memoria

  matrix_destroy(&m42);
  matrix_destroy(&mxu);
  matrix_destroy(&mxz);
  matrix_destroy(&zxm);
  matrix_destroy(&sum);
  matrix_destroy(&mult);
  matrix_destroy(&mult_sum);

  assert(m42 == nullptr);
  assert(mxu == nullptr);
  assert(mxz == nullptr);
  assert(zxm == nullptr);
  assert(sum == nullptr);
  assert(mult == nullptr);

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
  assert(sum == nullptr); // Esto arroja error cuando sum está asignada de manera que evitemos salir de la memoria asignada tratando de usar la matriz sum
  Matrix *bad_m = matrix(M+1, N, uniform);
  show_matrix("bad_m", bad_m);
  sum = matrix_sum(bad, bad_m);
  assert(sum == nullptr);
  Matrix *not_so_huge = matrix(2*M, 2*N, uniform);
  Matrix *nsh_seq = matrix(2*M, 2*N, sequence);
  sum = matrix_sum(not_so_huge, nsh_seq);
  show_matrix ( "sum_a_bit_bigger", sum);
  matrix_destroy(&sum);

  return 0;
}

/// prueba la multiplicacion de matrices
static int test_matrix_mult(int M, int N, int K) {
  Initializer sequence = get_initializer("i");
  Initializer uniform = get_initializer("u") ;

  Matrix *lhs = matrix(M, N, sequence);
  show_matrix("Matriz 1", lhs);
  Matrix *rhs = matrix(N, K, uniform);
  show_matrix("Matriz 2", rhs);


  Matrix *lhs_por_rhs = matrix_mult(lhs, rhs);
  show_matrix("Producto de dos matrices multiplicables", lhs_por_rhs);
  Matrix *conmut_nula = matrix_mult(rhs, lhs);
  assert(conmut_nula!=nullptr);
  show_matrix("conmut_nula", conmut_nula);
  
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
//h