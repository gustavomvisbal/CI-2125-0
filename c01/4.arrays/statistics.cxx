///
/// statistics.cxx
///
/// Funciones estadisticas basicas
///

#include "statistics.h"

#include <math.h>
#include <stdio.h>

/// computa el promedio de los valores en el arreglo x
/// n: tamano del arreglo
/// x: arreglo de datos
double mean(int n, const double x[]) {
  double sum = 0.0;
  for (int i = 0; i < n; ++i) {
    sum += x[i];
  }
  const double result = sum / n;
  return result;
}

/// computa la varianza de los valores en el arreglo x
/// utiliza la formula computacional para mejorar la eficiencia
/// n: tamano del arreglo
/// x: arreglo de datos
static double varp_ecf(int n, const double x[]) {
  double sx = 0.0;
  double sx2 = 0.0;
  for (int i = 0; i < n; ++i) {
    double xi = x[i];
    sx += xi;
    sx2 += xi * xi;
  }
  const double mean = sx / n;
  const double result = sx2 / n - mean * mean;
  return result;
}

/// computa la varianza de los valores en el arreglo x
/// utiliza la formula estandar de la definicion de varianza
/// n: tamano del arreglo
/// x: arreglo de datos
static double varp_sdf(int n, const double x[]) {
  double average = mean(n, x);
  double result=0.0;
  for(int i=0; i<n; ++i) {
    result+=(pow(x[i]-average, 2))/n;
  };
  return result;
}

/// computa la varianza de los valores en el arreglo x
/// verifica que la formula computacional es consitente con la definicion
/// n: tamano del arreglo
/// x: arreglo de datos
static double chequed_varp(int n, const double x[]) {
  double epsilon = 1E-9; // 1 * 10^-9
  double sdf_result =  varp_sdf(n, x);
  double ecf_result =  varp_ecf(n, x);
  // verificamos que la diferencia entre los resultados es negligible
  if (abs(sdf_result - ecf_result) / ecf_result > epsilon) {
    fprintf(stderr, "resultados inconsistentes: %lf <> %lf\n", sdf_result, ecf_result);
  }
  return ecf_result;
}

double varp(int n, const double x[]) {
  return chequed_varp(n, x);
}
