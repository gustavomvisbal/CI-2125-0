///
/// ihello.cxx
///

/// Especificación por ejemplos:
///
/// ihello => "Hello, world!"
/// ihello en => "Hello, world!"
/// ihello sp => "Hola, mundo!"
/// ihello en Raimundo => "Hello, Raimundo!"
/// ihello sp Raimundo => "Hola, Raimundo!"
///
/// Deben incluir el encabezado que declara a strcmp
///
/// Recuerden chequear que
/// - el número de argumentos es consistente
/// - el código internacional del lenguaje esta soportado
///
/// Proveer mensajes de error infomación 
///
/// Implentar solo dos o tres lenguajes, para no alargar el código demasiado
///

#include <stdio.h>
#include <string.h>

int main(int argc, const char *argv[])
{
  if (argc == 1) {
    fprintf(stdout, "Hello, World!\n");
  } else if (2 <= argc && argc <= 3) {
    if (strcmp(argv[1], "en")==0 && argc==2) {
      fprintf(stdout, "Hello, world!\n");
      // ...
    } else if (strcmp(argv[1], "sp")==0 && argc==2) {
      fprintf(stdout, "Hola, mundo!\n");
      // ...
    } else if (strcmp(argv[1], "en")==0 && strcmp(argv[2], "Raimundo")==0) {
      fprintf(stdout, "Hello, Raimundo!\n");
    } else if (strcmp(argv[1], "sp")==0 && strcmp(argv[2], "Raimundo")==0) {
      fprintf(stdout, "Hola, Raimundo!\n");
    }
    // ...
  } 
else {
    fprintf(stderr, "uso: %s <<< incompleto >>>\n", argv[0]);
    return 1;
  }
  return 0;
}
