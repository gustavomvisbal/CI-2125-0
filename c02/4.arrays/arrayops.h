///
/// arrayops.h
///
/// Operaciones con arreglos (Array operations)
///

///
/// Constructores y destructores
///

/// crea un arreglo de numeros (enteros) inicializados en cero
/// n: tamano del arreglo
int *int_array(int n);

/// crea un arreglo de numeros (doble precision) inicializados en cero
/// n: tamano del arreglo
double *double_array(int n);

/// crea un arreglo de numeros aleatorios uniformemente distribuidos
/// n: tamano del arreglo
double *random_uniform_array(int n);

/// crea un arreglo de numeros aleatorios normalmente distribuidos
/// n: tamano del arreglo
double *random_normal_array(int n);

/// crea un arreglo de strings (cadenas de caracteres) 
/// todos los elementos inicialmente apuntan a un mismo string nulo
/// n: tamano del arreglo
const char **string_array(int n);

/// libera la memoria reservada para un arreglo de cualquier tipo
/// n: tamano del arreglo
/// a: arreglo
void delete_array(void *a);

///
/// Operaciones de busqueda
///

/// posicion del numero (entero) k en el arreglo a
/// retorna la posicion del primer elemento con valor k en el arreglo a, o -1 si no encuentra
/// k: numero a buscar
/// n: tamano del arreglo
/// a: arreglo de numeros
int find_int(int k, int n, const int a[]);

/// posicion del "string" (cadena de caracteres) 's' en el arreglo 'a'
/// retorna la posicion del primer elemento igual a 's' en el arreglo 'a', o -1 si no encuentra
/// k: numero a buscar
/// n: tamano del arreglo
/// a: arreglo de numeros
int find_string(const char *s, int n, const char *const a[]);

/// posicion del menor elemento (numero entero) en el rango [i, j) de 'a'
/// retorna la posicion k del elemento de menor valor en el conjunto A[i] .. A[j-1]
/// i: posicion de arranque de la busqueda
/// j: posicion de terminacion de la busqueda (no incluida en el rango valido)
/// a: arreglo de numeros enteros
/// precondiciones: 0 <= i < j <= n, donde n es el tamano de 'a'
int find_min_int(int i, int j, const int a[]);

/// posicion del menor elemento (numero en doble precision) en el rango [i, j) de 'a'
/// retorna la posicion k del elemento de menor valor en el conjunto A[i] .. A[j-1]
/// i: posicion de arranque de la busqueda
/// j: posicion de terminacion de la busqueda (no incluida en el rango valido)
/// a: arreglo de numeros en doble precision
/// precondiciones: 0 <= i < j <= n, donde n es el tamano de 'a'
int find_min_double(int i, int j, const double a[]);

/// posicion del menor elemento (cadena de caracteres) en el rango [i, j) de 'a'
/// retorna la posicion k del elemento de menor valor en el conjunto A[i] .. A[j-1]
/// i: posicion de arranque de la busqueda
/// j: posicion de terminacion de la busqueda (no incluida en el rango valido)
/// a: arreglo de strings (cadenas de caracteres)
/// precondiciones: 0 <= i < j <= n, donde n es el tamano de 'a'
int find_min_string(int i, int j, const char *const a[]);

///
/// Operaciones para desordenar arreglos
///

/// barajea (desordena) un arreglo de numeros enteros
/// n: tamano del arreglo
/// a: arreglo
void shuffle_int_array(int n, int a[]);

/// barajea (desordena) un arreglo de numeros de doble precision
/// n: tamano del arreglo
/// a: arreglo
void shuffle_double_array(int n, double a[]);

/// barajea (desordena) un arreglo de "strings" (secuencias de caracteres)
/// n: tamano del arreglo
/// a: arreglo
void shuffle_string_array(int n, const char *a[]);

///
/// Operaciones para ordenar arreglos
///

/// ordena un arreglo de numeros enteros
/// n: tamano del arreglo
/// a: arreglo
void selection_sort_int_array(int n, int a[]);

/// ordena un arreglo de numeros en doble precision
/// n: tamano del arreglo
/// a: arreglo
void selection_sort_double_array(int n, double a[]);

/// ordena un arreglo de "strings" (cadenas de caracteres)
/// n: tamano del arreglo
/// a: arreglo
void selection_sort_string_array(int n, const char *a[]);
