#ifndef ERATOSTHENES_SEGMENTED_SIEVE_H
#define ERATOSTHENES_SEGMENTED_SIEVE_H
#include "kdutils.h"

struct normalized {
  int64 value;
  int index;
};

 normalized normalizer(int64 number);

class ess {
public:
  void generate(vector<unsigned char> &buffer, int64 min, int64 max);
  void showBuffer(unsigned char buffer[]);
  int isPrime(vector<unsigned char> &buffer, int64 number, int64 min);
  inline int getFlag(int64 block, int offset);
  int trivialPrimerTable[8] = {2, 3, 5, 7, 11, 13, 17, 19};

private:
};

#endif
