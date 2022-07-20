///
/// string concatenation
///
/// NOT like strcat: https://cplusplus.com/reference/cstring/strcat/
///

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// concatenate strings
/// const char *lhs: left hand side operand
/// const char *rhs: right hand side operand
const char *concatenate(const char *lhs, const char *rhs) {
  size_t lsize = strlen(lhs);
  size_t rsize = strlen(rhs);
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
