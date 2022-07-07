///
/// cryptic.cxx
///

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int UInt;
typedef unsigned short int Nugget;
typedef double Seed;

const Nugget NCLIPPER = 32768;
const Nugget RECURSER = 10000;
const Nugget K = 16;

Seed VISICALC =  M_PI - floor(M_PI) + 0.1979;
Seed ZENSHEET =  M_PI - floor(M_PI) + 0.1989;

Seed seed = VISICALC;

void reset_seed(Seed s) {
  seed = s;
}

Seed gfrac(Seed x) {
  return x - floor(x);
}

UInt r997() {
  seed = gfrac(seed * 997);
  return UInt(NCLIPPER * seed);
}

Nugget bhh[K][K] = 
{
 { 983, 971, 971, 929, 907, 911, 997, 983, 997, 971, 953, 991, 907, 997, 907, 907 },
 { 919, 977, 937, 953, 977, 953, 977, 991, 953, 911, 941, 967, 937, 919, 911, 983 },
 { 971, 977, 929, 947, 911, 977, 971, 977, 967, 977, 977, 967, 971, 941, 937, 967 },
 { 937, 967, 977, 947, 991, 977, 947, 971, 947, 991, 947, 991, 953, 937, 941, 983 },
 { 941, 937, 977, 967, 937, 983, 967, 997, 997, 911, 907, 919, 983, 971, 977, 991 },
 { 977, 941, 991, 947, 919, 983, 997, 997, 937, 941, 947, 929, 967, 919, 997, 919 },
 { 919, 937, 971, 977, 977, 907, 947, 941, 929, 977, 983, 929, 997, 983, 991, 919 },
 { 937, 971, 991, 983, 941, 971, 907, 983, 907, 953, 937, 977, 929, 983, 911, 919 },
 { 953, 967, 941, 941, 977, 977, 977, 971, 991, 953, 941, 911, 967, 971, 929, 907 },
 { 941, 919, 937, 937, 997, 919, 907, 911, 983, 941, 991, 959, 919, 967, 941, 983 },
 { 919, 911, 983, 929, 991, 919, 947, 911, 947, 983, 911, 967, 919, 937, 947, 997 },
 { 919, 947, 907, 919, 929, 919, 997, 929, 907, 919, 929, 919, 977, 971, 941, 907 },
 { 971, 907, 919, 947, 991, 983, 997, 953, 937, 941, 953, 919, 997, 919, 929, 947 },
 { 991, 983, 937, 997, 953, 937, 907, 983, 997, 911, 971, 911, 953, 937, 983, 929 },
 { 983, 953, 929, 941, 941, 947, 919, 907, 971, 929, 997, 983, 947, 907, 929, 983 },
 { 997, 997, 929, 967, 919, 911, 911, 907, 967, 977, 911, 911, 911, 971, 947, 947 }
};

Nugget rbhh() {
  Nugget i = r997() % K;
  Nugget j = r997() % K;
  return bhh[i][j];
}

Nugget tx(Nugget x, Nugget m, Nugget s) {
  return Nugget((UInt(x) * UInt(m) + UInt(s)) % NCLIPPER);
}

Nugget rooter(Nugget x) {
  Nugget m = rbhh();
  Nugget s = rbhh();
  return tx(x, m, s);
}

Nugget roto(Nugget N, Nugget x) {
  for (Nugget i = 0; i < N; ++i) {
    x = rooter(x);
  }
  return x;
}

Nugget nugget(const char *key) {
  Nugget result = 0;
  while (*key) {
    result = roto(RECURSER, result + *key++);
  }
  return result;  
}

void validate(int argc, const char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Uso: %s <clave>\n", argv[0]);
    fprintf(stderr, "Donde <clave> es su dirección de email de la universidad\n");
    exit(1);
  }
}

int main(int argc, const char *argv[]) {

  validate(argc, argv);
  const char *account = argv[1];

  reset_seed(VISICALC);
  Nugget visicalc = nugget(account);

  reset_seed(ZENSHEET);
  Nugget zensheet = nugget(account);

  fprintf(stdout, "Nuggets para %s: %5hd %5hd\n", account, visicalc, zensheet);

  return 0;
}
