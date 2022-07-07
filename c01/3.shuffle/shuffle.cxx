///
/// shuffle.cxx
///
/// "barajear" los elementos de un arreglo
///

#include <stdio.h>
#include <math.h>

double seed = 0.1415926539;

// genera enter aleatorio k tal que i <= k < N
int rand_index(int i, int N) {
  double w = 997 * seed;
  seed = w - floor(w);
  int j = i + int(floor((N - i) * seed));
  return j;
}

void swap_elements(double data[], int i, int j) {
  double tmp = data[i];
  data[i] = data[j];
  data[j] = tmp;
}

void swap_elements_desugared(double *data, int i, int j) {
  double tmp = *(data + i);
  *(data + i) = *(data + j);
  *(data + j) = tmp;
}

int main()
{
  double data[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0 };

  const int N = sizeof(data) / sizeof(data[0]);

  for (int i = 0; i < N; ++i) {
    int j = rand_index(i, N);
    // swap_elements(data, i, j);
    swap_elements_desugared(data, i, j);
  }

  for (int i = 0; i < N; ++i) {
    fprintf(stdout, "data[%d] = %lf\n", i, data[i]);
  }
  
  return 0;
}
