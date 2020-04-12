#ifndef BIG_HALF_GEAR_FACTORIZER_H
#define BIG_HALF_GEAR_FACTORIZER_H
#include "argumentsHandler.h"
#include "bigFactorObject.h"
#include "kdutils.h"
#include <pthread.h>
#include <gmpxx.h>
#define BIG_VALUES_FILE "bigHalfGearFactorizer.txt"
#define PRESIEVED_DIGITS 12

class bigHalfGearFactorizer {
public:
  vector<mpz_class> factors;
  void clear();
  void find(mpz_class n);
  void findMersenne(mpz_class n);
  string toString();
  vector<string> bigValues;
  bigHalfGearFactorizer();
  void saveBigValue(mpz_class v);


  private:
  void loadBigValues();
  void sortBigValues();

};

#endif