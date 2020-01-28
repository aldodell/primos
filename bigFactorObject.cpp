#include "bigFactorObject.h"

bigFactorObject::bigFactorObject(){

};

bigFactorObject::bigFactorObject(mpz_class base, int exponent)
{
    this->base = base;
    this->exponent = exponent;
};
