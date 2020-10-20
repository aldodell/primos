#ifndef MATHS_PRIME_H
#define MATHS_PRIME_H
#include <gmp.h>
#include <gmpxx.h>

/**
Rutinas comunes simples matemáticas
*/

/** Mersenne's prime exponents */
unsigned int MPE[] = {
    5,        13,       17,       61,       89,       521,      2281,
    3217,     4253,     9689,     9941,     11213,    19937,    21701,
    23209,    44497,    132049,   859433,   1398269,  2976221,  3021377,
    6972593,  13466917, 30402457, 32582657, 42643801, 43112609, 57885161,
    74207281, 77232917, 82589933};

// Evalúa si el número es de la forma 4k+3 (falso si es 4k+1)
bool is4k3(unsigned int n) {
  if ((n - 3) % 4 == 0) {
    return true;
  } else {
    return false;
  }
}

// Evalúa si el número es de la forma 4k+1 (falso si es 4k+3)
bool is4k1(unsigned int n) {
  if ((n - 1) % 4 == 0) {
    return true;
  } else {
    return false;
  }
}

// Devuelve true si todos sus factores son 4k+1 caso contrario false
bool areAll4k1(vector<unsigned int> &factors) {
  bool t = true;
  for (unsigned int f : factors) {
    t = t && is4k1(f);
  }
  return t;
}

struct factor {
  unsigned int base = 0;
  unsigned int exponent = 0;
  factor(unsigned int b, unsigned int e) {
    this->base = b;
    this->exponent = e;
  }
};

/**
 * Toma el parametro de entrada como un número entero y lo
 * factoriza.
 * Números de 32 bits sin signo
 * */

void factorizer(unsigned int n, vector<unsigned int> &factors) {
  unsigned int m;
  unsigned int p;

  // vector<unsigned int> factors;

  m = n;

  // Factorizar por 2 tantas veces sea posible
  while (true) {
    if (m % 2 != 0) {
      break;
    }
    m = m / 2;

    factors.push_back(2);

    if (m == 1)
      break;
  }

  // Factorizar los valores mayores a 2
  p = 3;
  while (true) {
    while (m % p == 0) {
      m = m / p;
      factors.push_back(p);
    }
    if (m == 1)
      break;
    p += 2;
  }

  return;
}

/**
 * Simple Eratosthenes approach sieve
 * For tiny numbers
 * */
bool isPrime(unsigned int n) {
  unsigned int p, r;

  if ((n & 1) == 0)
    return false;

  if (n % 5 == 0)
    return false;

  r = sqrt(n);
  p = 3;

  while (true) {
    if (n % p == 0)
      return false;
    p += 2;
    if (p > r)
      break;
  }
  return true;
}

#endif