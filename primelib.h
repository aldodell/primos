#ifndef PRIME_LIB
#define PRIME_LIB

#include "argumentsHandler.h"
#include "bigFactorObject.h"
#include "bigGearsFactorizer.h"
#include "bigHalfGearFactorizer.h"
#include "kdutils.h"
#include "maths_prime.h"
#include "primeTester.h"
#include "string"
#include <gmpxx.h>
#include <thread>

/** Return true if p is 4k+1 form or false if 4k+3 form */
bool is4k1(mpz_class p, int debugLevel = 1);
void test0(mpz_class a, mpz_class b, int debugLevel);
char *firstk(mpz_class p);

#endif
