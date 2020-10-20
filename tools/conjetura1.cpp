#include "conjetura1.h"
/**
Este programa prueba una teoría:
Busca números de Mersenne compuestos que tengan un factor 2pk+1 con
k=1
La suposición es que estos números tienen exponente 4k+3
pero al descomponer los exponentes (restando 1 y dividiendo por 2)
son todos de la forma 4k+1
*/

/* n = es el número a probar */

int main(int argc, char *argv[]) {

  vector<unsigned int> factors;
  string s;
  unsigned int m, factor1, t, boundry;
  bool all4k1;
  mpz_class mersenne;

  // Valor inicial
  unsigned int p = atoi(argv[1]);
  boundry = 10000000;

  while (true) {

    /*
        // Evaluamos si el número es de la forma 4k+3
        if (!is4k3(p)) {
          // printf("%d isn't 4k+3 form\n", n);
          goto nextN;
        }
        */

    // Cambiamos p por p-1/2
    /*
    m = (p - 1) / 2;
    factors.clear();
    factorizer(m, factors);

    // Revisamos que el valor tenga todos sus factores de la forma 4k+1
    all4k1 = areAll4k1(factors);

    if (!all4k1) {
      printf("%d have not all factors with 4k+1 form.\n", n);
      goto nextN;
    }

  printf("found: %d(%d)\n", p, m);
    */

    factor1 = (2 * p) + 1;

    if (!isPrime(factor1)) {
      // printf("2^%d-1; %d factor isn't prime. \n", p, factor1);
      goto nextN;
    }

    // printf("2^%d-1; %d factor is prime. \n", p, factor1);

    mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, p);
    mersenne--;

    if (mpz_divisible_ui_p(mersenne.get_mpz_t(), factor1) != 0) {
      // printf("2^%d-1 is divisible by %d\n", p, factor1);
      // printf("%d\n", p);
      printf("%d : %s\n==============\n", p, is4k1(p) ? "4k+1" : "4k+3");
      m = (p - 1) / 2;
      factors.clear();
      factorizer(m, factors);
      show4kXform(factors);
      printf("\n");

      // if (std::find(v.begin(), v.end(),value)!=v.end())
      if (find(factors.begin(), factors.end(), 3) != factors.end()) {
        printf("HAS 3!\n");
        break;
      }

      if (is4k1(p)) {
        printf("is 4k+1\n");
        break;
      }

      goto nextN;
    }

    // printf("Is prime? 2^%d-1 isn't divisible by %d\n", p, factor1);
    // break;

  nextN:
    p += 2;
    while (!isPrime(p))
      p += 2;

    if (p > boundry) {
      // printf("p=%d\n", p);
      break;
      boundry += 1000;
    }
  }
}