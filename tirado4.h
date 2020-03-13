#ifndef TIRADO4_H
#define TIRADO4_H
#include "argumentsHandler.h"
#include "kdutils.h"
#include "string"
#include <gmpxx.h>

struct factor {
  mpz_class base;
  mpz_class exp;
};



// Compares two intervals according to staring times. 
bool compareFactors(factor i1, factor i2) 
{ 
    return (i1.base < i2.base); 
} 


void tirado4a(int exponent, int debugLevel=0);
void tirado4b(int exponent, int debugLevel=0);
void tirado4c(int exponent, int debugLevel=0);

#endif
