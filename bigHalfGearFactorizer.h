#ifndef BIG_HALF_GEAR_FACTORIZER_H
#define BIG_HALF_GEAR_FACTORIZER_H
#include "argumentsHandler.h"
#include "bigFactorObject.h"
#include "kdutils.h"
#include <pthread.h>
#include <gmpxx.h>


class bigHalfGearFactorizer {
public:
  vector<mpz_class> factors;
  void clear();
  void find(mpz_class n);
  string toString();
  //bool stopThread = false;
};

#endif