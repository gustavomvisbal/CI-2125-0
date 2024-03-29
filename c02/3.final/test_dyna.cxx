///
/// Pruebas de arreglos dinamicos
///
/// deben ser extendidas
///

#include "test_dyna.h"
#include "dynarray.h"

#include <stdio.h>
#include <stdlib.h>

///
/// show_dynarray: imprime un arreglo dinamico
///
/// const Dynarray *dyna: apuntador a un arreglo dinamico
///
static void show_dynarray(const Dynarray *dyna) {

  size_t size = dyna_size(dyna);
  size_t capacity = dyna_capacity(dyna);
  const double *data = dyna_data(dyna);

  fprintf(stdout, "numero de elementos / capacidad: %u/%u\n", size, capacity);
  fprintf(stdout, "[\n");
  for (size_t i = 0; i < size; ++i) {
    fprintf(stdout, "  %6d: %12.6f\n", i, data[i]);
  }
  //El código de abajo intenta imprimir un sólo elemento en la posición i
  //como la posición 801702 no está definida para nuestro apuntador, nos devuelve fuera de rango
  //si usáramos notación data[] tendríamos un segmentation fault

  /*size_t i = 801702; // https://www.youtube.com/watch?v=5aQ1wFt82k4
  fprintf(stdout, "  %6d: %12.6f\n", i, dyna_val(i, dyna));
  fprintf(stdout, "]\n\n");*/
}

void next(const char *label, int L, int pos, int N) {
  fprintf(stdout, "<<< %s L=%d pos=%d N=%d >>>\n", label, L, pos, N);
}

int test_insert_remove() {
  Initializer index = get_initializer("i");
  Initializer fancy = get_initializer("f");
  // array length
  for (int L = 0; L < 4; ++L) {
    // allocate
    Dynarray *dyna = dynarray(L, index);
    // number of elements to insert
    for (int N = 1; N < 3; ++N) {
      // insertion position
      for (int i = 0; i <= L; ++i) {
        next("initial", dyna_size(dyna), i, N);
        show_dynarray(dyna);
        next("insert", dyna_size(dyna), i, N);
        dyna_insert(dyna, i, N, fancy);
        show_dynarray(dyna);
        next("remove", dyna_size(dyna), i, N);
        dyna_remove(dyna, i, N);
        show_dynarray(dyna);
      }
    }
    // deallocate
    dyna_destroy(&dyna);
  }
  return 0;
}

int test_sort() {
  Initializer normal = get_initializer("z");

  for (int L = 0; L < 4; ++L) {
    Dynarray *dyna = dynarray(L, normal);
    next("initial", dyna_size(dyna), 0, 0);
    show_dynarray(dyna);
    next("sorted", dyna_size(dyna), 0, 0);
    dyna_sort(dyna);
    show_dynarray(dyna);
    dyna_destroy(&dyna);
  }

  for (int L = 16; L <= 128; L *= 2) {
    Dynarray *dyna = dynarray(L, normal);
    next("initial", dyna_size(dyna), 0, 0);
    show_dynarray(dyna);
    next("sorted", dyna_size(dyna), 0, 0);
    dyna_sort(dyna);
    show_dynarray(dyna);
    dyna_destroy(&dyna);
  }
}

int test_dynamic_arrays_alt(int argc, const char *argv[]) {
  test_sort();
  // test_insert_remove();
}

bool alternative = true;

int test_dynamic_arrays(int argc, const char *argv[]) {
  if (alternative) {
    test_dynamic_arrays_alt(argc, argv);
    return 0;
  }
  // si argc es mayor o igual a 3, usar el parametro provisto
  const size_t NX_DEFAULT = 8;
  const size_t NX = (3 <= argc ? atoi(argv[2]) : NX_DEFAULT);

  Initializer init_x = get_initializer("z");

  Dynarray *x = dynarray(NX, init_x);
  show_dynarray(x);

  // si argc es mayor o igual a 4, usar el parametro provisto
  const size_t NY_DEFAULT = 16;
  const size_t NY = (4 <= argc ? atoi(argv[3]) : NY_DEFAULT);
  Initializer init_y = get_initializer("f");

  Dynarray *y = dynarray(NY, init_y);
  show_dynarray(y);

  Dynarray *result = dyna_concatenate(x, y);
  show_dynarray(result);

  //No crearé nuevos arrays, ya con x, y y result basta para hacer buenas pruebas =D
  //Primero prbamos el sort
  dyna_sort(result);
  show_dynarray(result);
  //Luego el insert y el remove
  if (6<=argc)
  {
    dyna_insert(result, (int) argv[4], (int) argv[5], get_initializer("u"));
    show_dynarray(result);
    dyna_sort(result);
    show_dynarray(result);
    dyna_remove(result, (int) argv[4], (int) argv[5]);
    show_dynarray(result);
  }
  //Prueba default de insert y remove
  else {
    dyna_insert(result, dyna_size(result), 4, get_initializer("f"));
    show_dynarray(result);
    dyna_sort(result);
    show_dynarray(result);
    dyna_remove(result, dyna_size(result)-4, 4);
    show_dynarray(result);
    dyna_insert(result, dyna_size(result)/2, 4, get_initializer("z"));
    show_dynarray(result);
    dyna_sort(result);
    show_dynarray(result);
    dyna_remove(result, dyna_size(result), 4);
    show_dynarray(result);
    dyna_insert(result, dyna_size(result)+1, 4, get_initializer("f"));

  }
  
  dyna_destroy(&result);
  dyna_destroy(&x);
  dyna_destroy(&y);

  return 0;    
}
//h
