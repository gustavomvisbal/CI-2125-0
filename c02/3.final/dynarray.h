///
/// dynarray.h
///

#ifndef _dynarray_h_
#define _dynarray_h_

#include "init.h"

#include <stdlib.h>

struct Dynarray;

///
/// constructor de arreglo dinamico
///
/// retorna el apuntador al nuevo arreglo dinamico
Dynarray *dynarray(size_t N, Initializer init);

///
/// destructor de arreglo dinamico
///
/// libera la memoria usada internamente por el arreglo dinamico y anula el apuntador
void dyna_destroy(Dynarray **dynarray);
/// Lo anterior es todo lo necesario para especificar la funcion
/// Lo que sigue es ayuda para entender las implicaciones
/// Noten la doble estrella
/// indica que el codigo del usuario debe pasar la *direccion* del apuntador ...
/// ... esto permite volver nulo el apuntador del cliente de la libreria (el usuario)
/// Liberar la memoria solo requeriria el *valor* del apuntador, no su *direccion*
/// Si no entienden lo anterior, significa que todavia no dominan apuntadores
/// Por favor, estudien, investiguen, discutan con otros estudiantes, y pregunten

///
/// funciones de acceso
///

/// retorna la direccion de la data en memoria, pero no permite modificarla
const double *dyna_data(const Dynarray *dyna);

/// retorna la cantidad de elementos en la data
size_t dyna_size(const Dynarray *dyna);

/// retorna la capacidad del arreglo que contiene la data
size_t dyna_capacity(const Dynarray *dyna);

///
/// manipulacion de arreglos dinamicos
///

///
/// insert
///
/// Inserta 'N' elementos a partir de la posicion 'pos'
/// Valida (no es una precondicion) que 'pos' esta en rango
/// Es decir: 0 <= 'pos' <= M, donde M es el tamaño del arreglo
/// Si la validacion falla, imprime un mensaje de error y retorna
/// Los elementos son inicializados usando funcion 'init'
/// Si 'init' es un apuntador nulo (nullptr) son inicializados en cero
void dyna_insert(Dynarray *dyna, int pos, int N, Initializer init);
/// Lo anterior es todo lo necesario para especificar la funcion
/// Estamos implementando arreglos dinamicos (duh!) por lo tanto:
/// Si el arreglo no tiene capacidad para agregar N elementos ...
/// ... hay que crear esa capacidad y copiar data de manera adecuada!
/// Si el arreglo tiene capacidad para agregar N elementos ...
/// ... no deben reservar nueva memoria y copiar data
/// Todo usuario de una libreria espera uso eficiente de recursos
/// Se evalua hacer manejo eficiente de la memoria, lo cual implica 
/// ... liberar (free) areas "viejas" de memoria, al ya no ser necesarias


///
/// remove
///
/// Elimina 'N' elementos a partir de la posicion 'pos'
/// Valida (no es una precondicion) que 'pos' esta en rango
/// Si la validacion falla, imprime un mensaje de error y retorna
/// Si hay menos de 'N' elementos a partir de 'pos' no da error ...
/// ... simplemente elimina todos los elementos a partir de 'pos'
void dyna_remove(Dynarray *dyna, int pos, int N);
/// Lo anterior es todo lo necesario para especificar la funcion
/// Lo que sigue es ayuda paraentender las implicaciones
/// La operacion siempre puede (y debe) hacerse sin reservar nueva memoria

///
/// sort
///
/// Ordena la data 'in situ' en orden creciente
void dyna_sort(Dynarray *dyna);
/// 'in situ' significa en la misma memoria del arreglo

///
/// concatenate
///
/// crea un arreglo dinamico que corresponde a la concatenacion de dos arreglos
Dynarray *dyna_concatenate(const Dynarray *dyna1, const Dynarray *dyna2);

#endif
