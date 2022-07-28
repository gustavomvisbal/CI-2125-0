///
/// names.cxx
///

#include "names.h"

#include "stochastic.h"

#include <stdio.h>
#include <string.h>

const char *first[] = {
  "Alicia",
  "Antonio",
  "Beatriz",
  "Benjamin",
  "Camila",
  "Carlos",
  "Daniela",
  "David",
  "Eduardo",
  "Emilia",
  "Florencia",
  "Francisco",
  "Gabriela",
  "Gustavo",
  "Heidy",
  "Hugo",
  "Ignacio",
  "Isabel",
  "Jorge",
  "Julia"
  "Kevin",
  "Kimberly",
  "Laura",
  "Luis",
  "Marco",
  "Mercedes",
  "Nelson",
  "Nina",
  "Olga",
  "Orlando",
  "Patricia",
  "Pedro",
  "Queen",
  "Quentin",
  "Raquel",
  "Ricardo",
  "Santiago",
  "Susana",
  "Talia",
  "Tobias",
  "Ulises",
  "Uma",
  "Valeria",
  "Victor",
  "Walter",
  "Winona",
  "Xavier",
  "Xeneida",
  "Yanet",
  "Yuri",
  "Zacarias",
  "Zena"
};

const char *last[] = {
  "Acevedo",
  "Benavides",
  "Cardenas",
  "Diaz",
  "Escalante",
  "Forlan",
  "Gutierrez",
  "Hernandez",
  "Iglesias",
  "Jimenez",
  "Kimura",
  "Linares",
  "Machado",
  "Navarro",
  "Oropeza",
  "Perez",
  "Quintana",
  "Ramirez",
  "Sandoval",
  "Tejada",
  "Urbano",
  "Velasquez",
  "Williams",
  "Xanthopoulos",
  "Yanez",
  "Zambrano"
};

// buffer para construir nombres usando snprintf
static const int BUFFER_SIZE = 128;
static char buffer[BUFFER_SIZE];

const char *random_name() {
  int NF = sizeof(first) / sizeof(first[0]);
  int NL = sizeof(last) / sizeof(last[0]);

  // random first name
  const char *f = first[int(NF * uniform())];

  // random middle initial (single letter)
  char m = random_int('A', 'Z' + 1);

  // random last name
  const char *l = last[int(NL * uniform())];

  // concatenacion de f (first), m (middle), y l (last)
  // aqui pueden ver el poder de snprintf para hacer el codigo mas compacto
  // pero tienen que estar mosca con esto: el buffer es compartido, asi que ...
  snprintf(buffer, BUFFER_SIZE, "%s %c. %s", f, m, l);

  // ... deben clonar el buffer usando strdup al retornar el resultado
  // https://cplusplus.com/reference/cstdio/snprintf/
  // https://en.cppreference.com/w/c/string/byte/strdup
  // preguntense: ¿que pasa si simplemente hacemos return buffer?

  const char *result = strdup(buffer);
  return result;

}
