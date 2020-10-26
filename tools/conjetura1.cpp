#include "conjetura1.h"
/**
Este programa prueba una teoría:
Busca números de Mersenne compuestos que tengan un factor 2pk+1 con
k=1
La suposición es que estos números tienen exponente 4k+3
pero al descomponer los exponentes (restando 1 y dividiendo por 2)
son todos de la forma 4k+1
*/

/*

 n = es el número a probar
 parametros:
 p1 = número inicial
 p2 = límite superior

  */

int main(int argc, char *argv[]) {

  vector<unsigned int> factors, commonFactors, primeTable;
  string s;
  unsigned int m, factor1, t, boundry;
  bool all4k1;
  mpz_class mersenne;

  // Valor inicial
  unsigned int p = atoi(argv[1]);
  boundry = atoi(argv[2]);

  // Creamos una tabla con números primos que vaya hasta el limite
  m = 2;
  primeTable.push_back(m);
  while (true) {
    m = nextPrime(m);
    if (m > p)
      break;
    primeTable.push_back(m);
    m = nextPrime(m);
  }

  while (true) {
    factor1 = (2 * p) + 1;
    if (isPrime(factor1)) {
      factors.clear();
      m = (p - 1) / 2;
      factorizer(m, factors);
      for (unsigned int f : factors) {
        if (find(commonFactors.begin(), commonFactors.end(), f) ==
            commonFactors.end()) {
          commonFactors.push_back(f);
        }
      }
    }

    p = nextPrime(p);

    if (p > boundry) {
      sort(commonFactors.begin(), commonFactors.end());

      for (unsigned int f :  primeTable) {
        if (find(commonFactors.begin(), commonFactors.end(), f) ==
            commonFactors.end()) {
          printf("%d\n", f);
        }
      }

      break;
    }
  }
}