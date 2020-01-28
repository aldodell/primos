#ifndef BIG_GEARS_FACTORIZER_H
#define BIG_GEARS_FACTORIZER_H
#include "argumentsHandler.h"
#include "bigFactorObject.h"
#include "kdutils.h"
#include "primeTester.h"
#include <gmpxx.h>

int bigFactorObjectCompare(bigFactorObject x, bigFactorObject y);

class bigGearsFactorizer {
public:
  bigGearsFactorizer();
  ~bigGearsFactorizer();
  vector<mpz_class> factors;
  void clear();
  void find(mpz_class n);
  string toString();
  primeTester *tester;

private:
  char lastDigit(mpz_class n);
};

#endif