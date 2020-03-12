#include "tirado4.h"

void calculate(int exponent) {

  vector<factor> factors;
  vector<mpz_class> factorials;

  mpz_class evenN = pow(2, exponent) - 2;
  mpz_class max = evenN + 1;
  mpz_class tmpMax;

  mpz_class k;

  mpz_class modK;
  mpz_class exp = 1;
  mpz_class pow2;

  mpz_class two = 2;

  factorials.push_back(max - 2);

  while (true) {
    // Store on pow2 the expression: 2^exp
    mpz_pow_ui(pow2.get_mpz_t(), two.get_mpz_t(), exp.get_ui());
    // tmpMax = pow2;

    while (true) {

      // Get module between evenN and pow2
      modK = evenN % pow2;
      // If module == 0 then proccess:
      if (modK == 0) {

        k = evenN / pow2;
        // Save power expression
        factor f;
        // base
        f.base = 2;
        // Exponent
        f.exp = exp * (((evenN - pow2) / (2 * pow2)) + 1);
        // Save it
        factors.push_back(f);
        // if (evenN / pow2) > 1 save it
        if (k > 1) {
          factorials.push_back(k);
        }
        // Decrease evenN
        evenN -= pow2;
        break;
      }
      evenN -= pow2;
    }

    // Increase exponent
    exp++;
    // Save on tmpMax 2^exp
    // If tmpMax > max then exit
    mpz_pow_ui(tmpMax.get_mpz_t(), two.get_mpz_t(), exp.get_ui());
    if (tmpMax > max)
      break;
  }

  mpz_class sumExp = 0;
  for (int i = 0; i < factors.size(); i++) {
    sumExp += factors[i].exp;
  }

  string fs = "";

  for (int i = 0; i < factorials.size(); i++) {
    fs = fs + factorials[i].get_str() + "! * ";
    // fs.push_back(factorials[i]);
  }
  fs.pop_back();
  fs.pop_back();

  // std::stringstream result;
  // std::copy(fs.begin(), fs.end(), std::ostream_iterator<int>(result, "! x
  // "));
  // result.str().c_str()
  gmp_printf("2^%Zd x %s", sumExp.get_mpz_t(), fs.c_str());
  cout << endl;
}

int main(int argc, char *argv[]) {
  argumentsHandler argHdl(argc, argv);
  int exponent;
  int debugLevel;
  int action;
  vector<int> primeTable{2,  3,  5,  7,  11, 13, 17, 19, 23, 29,
                         31, 37, 41, 43, 47, 53, 59, 61, 67};

  argHdl.add(argument(0, (char *)"n", (char *)"number",
                      (char *)"Number to be factorized", (char *)"N"));

  argHdl.add(argument(1, (char *)"d", (char *)"debug", (char *)"Debug level",
                      (char *)"N"));

  argHdl.add(argument(2, (char *)"u", (char *)"until",
                      (char *)"Process from 3 until N", (char *)"N"));

  argHdl.add(argument(3, (char *)"p", (char *)"primes",
                      (char *)"Process only prime table", (char *)"N"));

  while (action > -1) {
    action = argHdl.getAction();
    switch (action) {
    case 0:
      argHdl.pvalue(&exponent);
      calculate(exponent);
      cout << endl;
      break;
    case 1:
      argHdl.pvalue(&debugLevel);
      break;

    case 2:
      argHdl.pvalue(&exponent);
      for (int i = 3; i <= exponent; i += 2) {
        printf("2^%d-1: ", i);
        calculate(i);
        cout << endl;
      }
      break;

    case 3:
     // argHdl.pvalue(&exponent);
      for (int i = 0; i < primeTable.size(); i++) {
        printf("2^%d-1: ", primeTable[i]);
        calculate(primeTable[i]);
        cout << endl;
      }
      break;
    }
  }
}

// 2, 3, 5, 7, 11, 13, 17, 19, 23, 29. 31, 37, 41, 43, 47, 53, 59, 61, 67,