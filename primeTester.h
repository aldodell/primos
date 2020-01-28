#ifndef PRIME_TESTER_H
#define PRIME_TESTER_H
#include "argumentsHandler.h"
//#include "bigFactorObject.h"
//#include "bigGearsFactorizer.h"
#include "kdutils.h"
#include <gmpxx.h>
#define DATABASE_FILE "primeTesterDB.bin"

/*
65521 is last prime number close to 65536
Wich is root of 2^32...
Next prime number is 65537. So 65537^2 > 2^32
*/

#define MAX_INTEGER 4293001441 // 4294836225 // 4294967296
//18.429.861.372.428.076.481
//2.305.843.009.213.693.951


class primeTester {

public:
  // Constructor

  primeTester(int debugLevel = 0);
  bool test(string number);
  bool test(unsigned int number);
  unsigned int next(unsigned int bottom = 0);
  int debugLevel = 0;
  void reset();
  string factorize(string number);

private:
  void createDataBase();
  void loadDataBase();
  unsigned int getNumber(unsigned int index);
  vector<unsigned char> buffer;
  unsigned int initialTable[4] = {2, 3, 5, 7};
  unsigned int lastPrime;
  int deltaPrime;
  int deltas[4] = {2, 4, 2, 2}; // separation for 1,3,7,9
};

#endif