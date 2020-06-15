#ifndef BIG_HALF_GEAR_FACTORIZER_H
#define BIG_HALF_GEAR_FACTORIZER_H
#include "argumentsHandler.h"
#include "bigFactorObject.h"
#include "kdutils.h"
#include <gmpxx.h>
#include <pthread.h>
#define BIG_VALUES_FILE "bigHalfGearFactorizer.txt"
#define PRESIEVED_DIGITS 8

class bigHalfGearFactorizer {
public:
  unsigned int debug=0;
  vector<mpz_class> factors;
  void clear();
  void find(mpz_class n);
  void findMersenne(mpz_class n);
  string toString(bool test4k1 = false);
  string toString(vector<mpz_class> factors, bool test4k1 = false);
  vector<string> bigValues;
  bigHalfGearFactorizer();
  void saveBigValue(mpz_class v);
  string divideBy(vector<mpz_class> dividend, vector<mpz_class> divisor,
                  bool test4k1 = false);

private:
  void loadBigValues();
  void sortBigValues();
};

#endif