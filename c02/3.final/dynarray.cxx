///
/// dynamic array operations
///

#include "dynarray.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/// Nuestro glorioso arreglo dinamico (dynarray: dynamic array)
///
/// Es un triple:
/// data: apuntador al arreglo que contiene los datos
/// size: tamaño de los datos, es decir el numero de elementos en la data
/// capacity: la capacidad total del arreglo
/// 
/// La capacidad es el numero maximo de elementos que el dynarray puede contener ...
/// ... sin requerir una nueva reservacion de memoria para la data.
///
/// La diferencia (capacity - size) es la holgura del arreglo de data
/// Otra forma de verlo es que corresponde a la cantidad de "basura" :-)
///
/// Los campos de esta estructura no son directamente visibles
/// El encabezado solo declara 'struct Dynarray' sin revelar su estructura!
///
/// Esto (casi) garantiza que el usuario no puede corromper la implementacion
///
/// Todo lo que el cliente de la libreria (usuario) necesita esta provisto en la interfaz

struct Dynarray {
  double *data;
  size_t size;
  size_t capacity;
};

Dynarray *dynarray(size_t N, Initializer init) {
  Dynarray *dyna = (Dynarray *) malloc(sizeof(Dynarray));
  dyna->size = N;
  dyna->capacity = N;
  dyna->data = (double *) malloc(dyna->capacity * sizeof(double));
  for (size_t i = 0; i < dyna->size; ++i) {
    dyna->data[i] = init(i);
  }
  return dyna;
}

void dyna_destroy(Dynarray **dynarray) {
  free((*dynarray)->data);
  (*dynarray)->data = nullptr;
  free(*dynarray);
  *dynarray = nullptr;
}

double dyna_val(size_t i, const Dynarray *dyna) {
  if (dyna->size <= i) {
    fprintf(stderr, "indice %zu fuera de rango [0-%zu)\n", i, dyna->size);
    return nan("out of range");
  }
  return dyna->data[i];
}

void dyna_assign(size_t i, Dynarray *dyna, double val) {
  if (dyna->size <= i) {
    fprintf(stderr, "indice %zu fuera de rango [0-%zu)\n", i, dyna->size);
    return;
  }
  dyna->data[i] = val;
}

/// advertencia: esto permite que el usuario tenga acceso a los datos sin chequeos
/// pero: 1) es mas eficiente y 2) el valor retornado permite usar la notacion a[i]
const double *dyna_data(const Dynarray *dyna) {
  return dyna->data;
}

size_t dyna_capacity(const Dynarray *dyna) {
  return dyna->capacity;
}

size_t dyna_size(const Dynarray *dyna) {
  return dyna->size;
}

//La función original era void, pero no conseguí cómo guardar la dirección de dyna antes de borrarla, así
Dynarray *dyna_insert(Dynarray *dyna, int pos, int N, Initializer init) {
  size_t size = dyna_size(dyna);
  size_t cap = dyna_capacity(dyna);
  if (pos>size) {
    fprintf(stdout, "Los nuevos elementos deben agregarse desde un índice mayor o igual al tamaño del arreglo\n");
    return dyna;
  }
  //Como se puede apreciar, existe la posibilidad de que se reescriban datos
  if (cap-size<N && cap-pos<N) {
    double data[size];
    for (int i = 0; i<size; ++i) {
    data[i] = dyna_val(i, dyna);
    }
    dyna_destroy(&dyna);
    Dynarray *dyna = (Dynarray *) malloc(sizeof(Dynarray));
    dyna->size = pos+N;
    dyna->capacity = N+pos;
    dyna->data = (double *) malloc((pos+N)* sizeof(double));
    for (size_t i = 0; i < pos+N; ++i) {
      if (i<pos) {
        dyna_assign(i, dyna, data[i]);
      }
      else {
        dyna_assign(i, dyna, init(i));
      }
    }
    free(data);
    return dyna;
  }  
  else if (cap-size>N || cap-pos>N){
    for (size_t i = size; i<N; ++i) {
      dyna->data[i] = init(i);
    }
    return dyna;
  }
  
}

void dyna_remove(Dynarray *dyna, int pos, int N) {
  size_t size = dyna_size(dyna);
  size_t cap = dyna_capacity(dyna);
  if (pos>=size) {
    fprintf(stdout, "Los elementos a eliminar deben estar dentro del tamaño del arreglo\n");
    return;
  }
  for (size_t i = pos; i<size; ++i) {
    dyna->data[i] = 0;
  }
}

int find_min_double(int i, int j, const double a[]) {
  int mindx = i;
  double min = a[mindx];
  for (i; i<j; ++i) {
    if (min>a[i]) {
      mindx=i;
      min=a[mindx];
    }
  }
  return mindx;
}

void dyna_sort(Dynarray *dyna) {
  for (int i = 0; i<dyna_size(dyna)-1; ++i) {
    int mindx = find_min_double(i, dyna_size(dyna), dyna->data);
    double tmp=dyna->data[i];
    dyna->data[i]=dyna->data[mindx];
    dyna->data[mindx]=tmp;
  }
}

Dynarray *dyna_concatenate(const Dynarray *dyna1, const Dynarray *dyna2) {
  size_t S1 = dyna1->size;
  size_t S2 = dyna2->size;
  int N= S1+S2;
  Dynarray *result = (Dynarray *) malloc(sizeof(Dynarray));
  result->size = S1+S2;
  result->capacity = S1+S2;
  result->data = (double *) malloc(N*sizeof(double));
  for (int i = 0; i<N; ++i){
    if (i<S1){
      result->data[i] = dyna1->data[i];
    }
    else {
      result->data[i] = dyna2->data[i-S1];
    }
  }
  return result;
}
