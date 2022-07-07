///
/// average.cxx
///
/// calcula el valor promedio de un arreglo de datos
///

#include <stdio.h>

int main()
{
  const double data[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0 };

  fprintf(stdout, "data tiene %lld octodios\n", sizeof(data));

  const int N = sizeof(data) / sizeof(data[0]);

  double sum = 0.0;

  int i = 0;
  while (i < N) {
    sum = sum + data[i];
    i = i + i;
  }

  const double promedio = sum / N;
  
  fprintf(stdout, "promedio(data) = %lf\n", promedio);
 
  return 0;
}
