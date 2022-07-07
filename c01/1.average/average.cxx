///
/// average.cxx
///
/// calcula el valor promedio de un arreglo de datos
///

#include <stdio.h>

int main()
{
  const double data[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, };

  const int N = sizeof(data) / sizeof(data[0]);

  double sum = 0.0;

  for (int i = 0; i < N; ++i) {
    sum += data[i];
  }

  const double average = sum / N;
  
  fprintf(stdout, "promedio(data) = %lf\n", average);

  return 0;
}
