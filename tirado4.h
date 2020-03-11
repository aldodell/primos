#ifndef TIRADO4_H
#define TIRADO4_H
#include "argumentsHandler.h"
#include "kdutils.h"
#include "string"
#include <gmpxx.h>

struct factor {
  int base;
  int exp;
};

void calculate(int exp);
#endif
