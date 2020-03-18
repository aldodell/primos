#include "bigFactorObject.h"




bigFactorObject::bigFactorObject(){

};

bigFactorObject::bigFactorObject(mpz_class base, int exponent)
{
    this->base = base;
    this->exponent = exponent;
};

int bigFactorObjectCompare(bigFactorObject x, bigFactorObject y) {
  return x.base < y.base;
}
