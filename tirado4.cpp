#include "tirado4.h"

void calculate(int exponent) {

  vector<factor> factors;
  vector<int> factorials;

  int evenN = exponent - 1;
  int k;

  int modK;
  int exp = 1;
  int pow2;

  while (true) {
    while (true) {

      pow2 = pow(2, exp);
      modK = evenN % (int)pow2;
      if (modK == 0) {
        k = evenN / pow2;
        factor f;
        f.base = 2;
        f.exp = exp * (((evenN - pow2) / (2 * pow2)) + 1);
        factors.push_back(f);
        factorials.push_back(k);
        evenN -= 2;
        break;
      }
      evenN -= 2;
    }

    exp++;
    if (pow(2, exp) > exponent)
      break;
  }

  int sumExp = 0;
  for (int i = 0; i < factors.size(); i++) {
    sumExp += factors[i].exp;
  }
  factorials.push_back(exponent - 1);
  string fs;
  

  printf("2^%d x %s", sumExp, "");
}

int main(int argc, char *argv[]) {
  argumentsHandler argHdl(argc, argv);
  int exponent;
  int debugLevel;
  int action;

  argHdl.add(argument(0, (char *)"n", (char *)"number",
                      (char *)"Number to be factorized", (char *)"N"));

  argHdl.add(argument(1, (char *)"d", (char *)"debug", (char *)"Debug level",
                      (char *)"N"));

  while (action > -1) {
    action = argHdl.getAction();
    switch (action) {
    case 0:
      argHdl.pvalue(&exponent);
      //  n = argHdl.value;
      break;
    case 1:
      argHdl.pvalue(&debugLevel);
      break;
    }
  }

  calculate(exponent);
}