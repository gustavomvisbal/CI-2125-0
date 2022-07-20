///
/// examples of undefined behavior
///
/// los comentarios // U indican comportamiento indefinido
///

#include <stdio.h>
#include <stdlib.h>

void f() {

  int a[] = { 67, 42 };

  int *p = nullptr;
  
  p = a;     // <== valido
  p = &a[0]; // <== valido (y equivalente al anterior)
  p = &a[1]; // <== valido
  p = &a[2]; // <== TAMBIEN es valido (pero intentar *p ahora no lo es)
  p = &a[3]; // <== NO es valido

  for (int *p = &a[0]; p < &a[2]; ++p) {
    fprintf(stdout, "p: %p\n", p);
    fprintf(stdout, "%d\n", *p);
  }
}

void g() {

  int *a = (int *) malloc(6 * sizeof(int));

  int *p = nullptr;
  
  p = a;     // <== valido
  p = &a[0]; // <== valido (y equivalente al anterior)
  p = &a[1]; // <== valido
  // ...
  p = &a[5]; // <== valido
  p = &a[6]; // <== TAMBIEN es valido (pero intentar *p ahora no lo es)
  p = &a[7]; // <== NO es valido

  for (int *p = &a[0]; p < &a[2]; ++p) {
    fprintf(stdout, "p: %p\n", p);
    fprintf(stdout, "%d\n", *p);
  }
}

// el ordern de evaluacion de argumentos (funciones y operadores) no esta definido
void h() {

  int x = 7;
  int r = x + ++x; // U
  fprintf(stdout, "r: %d\n", r);

  x = 7;
  r = ++x + x; // U
  fprintf(stdout, "r: %d\n", r);

  x = 7;
  r = x + x++; // U
  fprintf(stdout, "r: %d\n", r);

  x = 7;
  r = x++ + x; // U
  fprintf(stdout, "r: %d\n", r);
}

// en la asignacion, el orden de evaluacion del lhs y el rhs no esta definido
void pekas() {

  int x[2];

  int i = 0;
  x[0] = 7;
  x[1] = 9;

  x[i] = 42 + i++; // U
  fprintf(stdout, "x: [%d, %d]\n", x[0], x[1]);

  i = 0;
  x[0] = 7;
  x[1] = 9;

  x[i++] = 42 + i; // U
  fprintf(stdout, "x: [%d, %d]\n", x[0], x[1]);

  i = 0;
  x[0] = 7;
  x[1] = 9;

  x[i] = 42 + ++i; // U
  fprintf(stdout, "x: [%d, %d]\n", x[0], x[1]);

  i = 0;
  x[0] = 7;
  x[1] = 9;

  x[++i] = 42 + i; // U
  fprintf(stdout, "x: [%d, %d]\n", x[0], x[1]);
}


// el ordern de evaluacion de argumentos (funciones y operadores) no esta definido

void swap(int *x, int *y) {
  int t = *x;
  *x = *y;
  *y = t;
}

void weird(int x, int y, int z) {
  // fprintf(stdout, "weird\t(x, y, z): (%d, %d, %d)\n", x, y, z);
}

void strange() {
  fprintf(stdout, "--------\n");

  int a = 67;
  int b = 42;

  // vamos a intercambiar los valores de a y b de varias maneras

  int t = a;
  a = b;
  b = t;
  fprintf(stdout, "swap 0:\t(a, b): (%d, %d)\n", a, b);

  a = 67;
  b = 42;
  swap(&a, &b);
  fprintf(stdout, "swap 1:\t(a, b): (%d, %d)\n", a, b);

  a = 67;
  b = 42;
  (t = a, a = b, b = t);
  fprintf(stdout, "swap 2:\t(a, b): (%d, %d)\n", a, b);

  a = 67;
  b = 42;
  weird(t = a, a = b, b = t); // U
  fprintf(stdout, "swap 3:\t(a, b): (%d, %d)\n", a, b);

  a = 67;
  b = 42;
  weird(b = t, a = b, t = a); // U
  fprintf(stdout, "swap 4:\t(a, b): (%d, %d)\n", a, b);

}

int main()
{
  f();
  g();
  h();
  pekas();
  strange();
  return 0;
}
