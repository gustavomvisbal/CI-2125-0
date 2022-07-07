///
/// sizes.cxx
///
/// muestra el tamaño en memoria de variables de varios tipos
///

#include <stdio.h>

int main()
{
  fprintf(stdout, "bool ............. %2zu\n", sizeof(bool));

  fprintf(stdout, "char ............. %2zu\n", sizeof(char));

  fprintf(stdout, "short int ........ %2zu\n", sizeof(short int));

  fprintf(stdout, "int .............. %2zu\n", sizeof(int));

  fprintf(stdout, "long int ......... %2zu\n", sizeof(long int));

  fprintf(stdout, "long long int .... %2zu\n", sizeof(long long int));

  fprintf(stdout, "float ............ %2zu\n", sizeof(float));

  fprintf(stdout, "double ........... %2zu\n", sizeof(double));

  fprintf(stdout, "long double ...... %2zu\n", sizeof(long double));

  fprintf(stdout, "pointer .......... %2zu\n", sizeof(void *));

  fprintf(stdout, "size_t ........... %2zu\n", sizeof(size_t));

  return 0;
}
