///
/// string concatenation
///
/// NOT like strcat: https://cplusplus.com/reference/cstring/strcat/
///

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *pera = "pera";
const char *lima = " lima";

/// concatenate strings
/// const char *str1: left hand side operand
/// const char *str2: right hand side operand
const char *concatenate(const char *str1, const char *str2) {
  size_t L1 = strlen(str1);
  size_t L2 = strlen(str2);
  char *result = (char *) malloc((L1 + L2 + 1) * sizeof(char));
  strcpy(result, str1);
  strcpy(&result[L1], str2);
  return result;
}


const char *whiskey = "whiskey ";
const char *tango = "tango ";
const char *fox = "fox ";

int main(int argc, const char *argv[])
{
  assert(argc <= 2);
  int k = (argc == 1 ? 0 : atoi(argv[1]));

  const char *kleene_tango = "";
  for (int i = 0; i < k; ++i) {
     kleene_tango = concatenate(kleene_tango, tango);
  }

  const char *result = concatenate(whiskey, concatenate(kleene_tango, fox));

  fprintf(stdout, "result: %s\n", result);
  return 0;
}
