///
/// init.h
/// Funciones para inicializar elementos
/// Convenientes para probar matrices y arreglos dinamicos
///

#ifndef _init_cxx_
#define _init_cxx_

///
/// tipo de las funciones que inicializan elementos de un dynarray
///
/// toman un argumento de tipo entero y regresan un valor de doble precision
typedef double (*Initializer)(int i);

///
/// get_initializer
/// retorna una funcion de inicializacion predefinida de acuerdo a la seleccion
///
/// const char *choice: identifica la funcion deseada con un codig de tipo string
///
/// los codigos de seleccion y su significado son:
///
/// "0": inicializa cada elemento con 0.0
/// "42": inicializa cada elemento con el valor 42.0
/// "i": inicializa de acuerdo al valor del argumento 'i', convertido a 'double'
/// "u": inicializa elementos con numeros aleatorios entre 0 y 1
/// "z": inicializa elementos con numero aleatorios tomados de la distribucion Z
/// "f": parecido a "i", pero agregando un numero aleatorio entre 0 y 1
/// 
Initializer get_initializer(const char *choice);

#endif
