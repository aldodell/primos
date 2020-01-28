#ifndef BIG_FACTOR_OBJECT_H
#define BIG_FACTOR_OBJECT_H
#include <gmp.h>
#include <gmpxx.h>

class bigFactorObject {
public:
  mpz_class base;
  int exponent;
  bigFactorObject();
  bigFactorObject(mpz_class base, int exponent);
};

#endif
