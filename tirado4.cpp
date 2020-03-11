#include "tirado4.h"

void calculate(int exponent) {


  vector<factor> factors;
  vector<int> factorials;

  int64 evenN = pow(2, exponent) - 2;
  int64 max = evenN + 1;

  int64 k;

  int64 modK;
  int64 exp = 1;
  int64 pow2;
  factorials.push_back(max - 2);

  while (true) {
    while (true) {

      pow2 = pow(2, exp);
      modK = evenN % pow2;
      if (modK == 0) {
        k = evenN / pow2;
        factor f;
        f.base = 2;
        f.exp = exp * (((evenN - pow2) / (2 * pow2)) + 1);
        factors.push_back(f);
        if (k > 1) {
          factorials.push_back(k);
        }
        evenN -= 2;
        break;
      }
      evenN -= 2;
    }

    exp++;
    if (pow(2, exp) > max)
      break;
  }

  int sumExp = 0;
  for (int i = 0; i < factors.size(); i++) {
    sumExp += factors[i].exp;
  }

  string fs = "";

  for (int i = 0; i < factorials.size(); i++) {
    fs = fs + to_string(factorials[i]) + "! x";
    // fs.push_back(factorials[i]);
  }

  // std::stringstream result;
  // std::copy(fs.begin(), fs.end(), std::ostream_iterator<int>(result, "! x
  // "));
  // result.str().c_str()
  printf("2^%d x %s", sumExp, fs.c_str());
  cout << endl;
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