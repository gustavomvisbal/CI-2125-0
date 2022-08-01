///
/// matrix.cxx
///

#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

typedef double (*Initializer)(int i);

struct Matrix {
  double **data;
  size_t NR;
  size_t NC;
};

Matrix *matrix(size_t NR, size_t NC, Initializer init) {
  Matrix *result = (Matrix *) malloc(sizeof(Matrix));
  result->NR = NR;
  result->NC = NC;
  result->data = (double **) malloc(NR * sizeof(double *));
  for (size_t i = 0; i < NR; ++i) {
    result->data[i] = (double *) malloc(NC * sizeof(double));
    for (size_t j = 0; j < NC; ++j) {
      result->data[i][j] = init(NC * i + j);
    }
  }
  return result;
}

void matrix_destroy(Matrix **matrix) {
  size_t NR = (*matrix)->NR;
  for (size_t i = 0; i < NR; ++i) {
    free((*matrix)->data[i]);
    (*matrix)->data[i] = nullptr;
  }
  free((*matrix)->data);
  (*matrix)->data = nullptr;
  free(*matrix);
  *matrix = nullptr;
}

const double **matrix_data(const Matrix *matrix) {
  return (const double **) matrix->data;
}

size_t matrix_nr(const Matrix *matrix) {
  return matrix->NR;
}

size_t matrix_nc(const Matrix *matrix) {
  return matrix->NC;
}

Matrix *matrix_sum(const Matrix *lhs, const Matrix *rhs) {
  size_t LNR = lhs->NR;
  size_t LNC = lhs->NC;
  size_t RNR = rhs->NR;
  size_t RNC = rhs->NC;
  // if lhs and rhs are not conformant, print error and return null
  if (LNR != RNR || LNC != RNC) {
    fprintf(stderr, "Error: matrices que no tienen la misma forma no pueden ser sumadas: ");
    fprintf(stderr, "(%zux%zu) != (%zux%zu)\n", LNR, LNC, RNR, RNC);
    return nullptr;
  }
  Matrix *result = (Matrix *) malloc(sizeof(Matrix));
  result->NR = LNR;
  result->NC = LNC;
  result->data = (double **) malloc(LNR * sizeof(double *));
  for (size_t i = 0; i < LNR; ++i) {
    result->data[i] = (double *) malloc(LNC * sizeof(double));
    for (size_t j = 0; j < LNC; ++j) {
      result->data[i][j] = lhs->data[i][j] + rhs->data[i][j];
    }
  }
  return result;
}

Matrix *matrix_mult(const Matrix *lhs, const Matrix *rhs) {
  size_t LNR = lhs->NR;
  size_t LNC = lhs->NC;
  size_t RNR = rhs->NR;
  size_t RNC = rhs->NC;
  // if LNR and RNC are not equal, it can't be executed
  if (LNC != RNR) {
    fprintf(stdout, "Error: El número de filas de la matriz 1 no es igual al número de columnas de la matriz 2: ");
    fprintf(stdout, "%zu != %zu\n", LNC, RNR);
    return nullptr;
  }
  Matrix *result = (Matrix *) malloc(sizeof(Matrix));
  result->NR = RNC;
  result->NC = LNR;
  result->data = (double **) malloc(RNC * sizeof(double *));
  for (size_t i = 0; i < RNC; ++i) {
    result->data[i] = (double *) malloc(LNR * sizeof(double));
    for (size_t j = 0; j < LNR; ++j) {
      for (size_t k = 0; k<RNR; ++k) {
        result->data[i][j] += lhs->data[j][k] * rhs->data[k][i];
      }
    }
  }
  return result; 
}
