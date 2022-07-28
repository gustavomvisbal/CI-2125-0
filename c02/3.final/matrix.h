///
/// matrix.h
///

#ifndef _matrix_h_
#define _matrix_h_

#include "init.h"

#include <stdlib.h>

struct Matrix;

///
/// constructor de matriz
///
/// retorna el apuntador a la matriz
Matrix *matrix(size_t NR, size_t NC, Initializer init);

///
/// destructor de matriz
///
/// libera la memoria usada internamente por la matriz y anula el apuntador
void matrix_destroy(Matrix **matrix);
/// Lo anterior es todo lo necesario para especificar la funcion
/// Lo que sigue es ayuda para entender las implicaciones
/// Noten la doble estrella
/// indica que el codigo del usuario debe pasar la *direccion* del apuntador ...
/// ... esto permite volver nulo el apuntador del cliente de la libreria (el usuario)
/// Liberar la memoria solo requeriria el *valor* del apuntador, no su *direccion*
/// Si no entienden lo anterior, significa que todavia no dominan apuntadores
/// Por favor, estudien, investiguen, discutan con otros estudiantes, y pregunten

/// retorna el numero de filas de la matriz
size_t matrix_nr(const Matrix *matrix);

/// retorna el numero de columnas de la matriz
size_t matrix_nc(const Matrix *matrix);

/// retorna un apuntador a la data
const double **matrix_data(const Matrix *matrix);

/// retorna la suma de dos matrices
///
/// el numero de filas y columnas de ambas matrices debe coincidir
Matrix *matrix_sum(const Matrix *lhs, const Matrix *rhs);

/// retorna el producto de dos matrices
///
/// si las matrices no se pueden multiplicar
/// - imprime un mensaje de error descriptivo
/// - retorna un apuntador nulo
Matrix *matrix_mult(const Matrix *lhs, const Matrix *rhs);
/// https://en.wikipedia.org/wiki/Matrix_multiplication
/// recuerden: para multiplicar las matrices, se debe cumplir:
/// matrix_nc(lhs) == matrix_nr(rhs)

#endif
