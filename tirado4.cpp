#include "tirado4.h"

void tirado4a(int exponent, int debugLevel) {

  vector<factor> factors;
  vector<mpz_class> factorials;

  mpz_class evenN;
  // mpz_class max = evenN + 1;
  // mpz_class tmpMax;
  mpz_class k;
  mpz_class modK;
  mpz_class exp = 1;
  mpz_class pow2;
  mpz_class two = 2;
  bool done = false;

  // = pow(2, exponent) - 2;

  // Get 2^exponent (from argument function caller)
  mpz_pow_ui(evenN.get_mpz_t(), two.get_mpz_t(), exponent);
  // Save 2^exponent
  // tmpMax = evenN;
  // Set even value: (2^exponent - 1) -1
  evenN = evenN - 2;

  factorials.push_back(evenN - 1);

  while (true) {
    // Set pivot factor 2^exp
    mpz_pow_ui(pow2.get_mpz_t(), two.get_mpz_t(), exp.get_ui());

    // cout << endl;
    while (true) {
      // Evaluate if evenN is divisible by 2^exp
      modK = evenN % pow2;
      if (modK == 0) {

        k = evenN / pow2;
        factor f;
        f.base = 2;
        f.exp = exp * (((evenN - pow2) / (2 * pow2)) + 1);
        // cout << f.exp << endl;

        if (debugLevel > 0) {

          gmp_printf("2^%Zd^{[(%Zd - %Zd) / %d] + 1} = %Zd", exp.get_mpz_t(),
                     evenN.get_mpz_t(), pow2.get_mpz_t(), 2 * pow2.get_ui(),
                     f.exp.get_mpz_t());
          cout << endl;
        }

        factors.push_back(f);
        if (k > 1) {
          factorials.push_back(k);
        }
        done = true;
      }
      // Decrease even N by 2^exp
      evenN -= pow2;
      if (done) {
        done = false;
        break;
      }
      // If is reached end, exit
      if (evenN < pow2) {
        break;
      }
    }

    exp++;
    if (exp == exponent)
      break;
  }

  mpz_class sumExp = 0;
  for (int i = 0; i < factors.size(); i++) {
    sumExp += factors[i].exp;
  }

  string fs = "";

  for (int i = 0; i < factorials.size(); i++) {
    fs = fs + factorials[i].get_str() + "! * ";
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

void tirado4b(int exponent, int debugLevel) {

  mpz_class k;
  mpz_class value;
  mpz_class pow2;
  mpz_class modK;
  int exp;
  exp = 1;

  mpz_ui_pow_ui(value.get_mpz_t(), 2, exponent);
  value = value - 2;
  cout << endl;

  while (true) {
    mpz_ui_pow_ui(pow2.get_mpz_t(), 2, exp);
    modK = value % pow2;
    if (modK == 0) {
      k = value / pow2;
      gmp_printf("2^%d-1-1 => 2^%d * %Zd", exponent, exp, k.get_mpz_t());
      cout << endl;
    }
    value = value - pow2;
    exp++;
    if (exp == exponent)
      break;
  }
}

int main(int argc, char *argv[]) {
  argumentsHandler argHdl(argc, argv);
  int exponent;
  int debugLevel;
  int action;
  vector<int> primeTable{
      2,  3,  5,  7,  11, 13, 17, 19, 23, 29,
      31, 37, 41, 43, 47, 53, 59, 61}; //,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199};

  argHdl.add(argument(0, (char *)"n", (char *)"number",
                      (char *)"Number to be factorized", (char *)"N"));

  argHdl.add(argument(1, (char *)"d", (char *)"debug", (char *)"Debug level",
                      (char *)"N"));

  argHdl.add(argument(2, (char *)"u", (char *)"until",
                      (char *)"Process from 3 until N", (char *)"N"));

  argHdl.add(argument(3, (char *)"p", (char *)"primes",
                      (char *)"Process only prime table", (char *)"N"));

  argHdl.add(argument(4, (char *)"a", (char *)"aldo test",
                      (char *)"Process only prime table", (char *)"N"));

  while (action > -1) {
    action = argHdl.getAction();
    switch (action) {
    case 0:
      argHdl.pvalue(&exponent);
      printf("2^%d-1:\r\n", exponent);
      tirado4a(exponent, debugLevel);
      cout << endl;
      break;
    case 1:
      argHdl.pvalue(&debugLevel);
      break;

    case 2:
      argHdl.pvalue(&exponent);
      for (int i = 3; i <= exponent; i += 2) {
        printf("2^%d-1:\r\n ", i);
        tirado4a(i, debugLevel);
        cout << endl;
      }
      break;

    case 3:
      // argHdl.pvalue(&exponent);
      for (int i = 0; i < primeTable.size(); i++) {
        printf("2^%d-1: \r\n", primeTable[i]);
        tirado4a(primeTable[i], debugLevel);
        cout << endl;
      }
      break;

    case 4:
      argHdl.pvalue(&exponent);
      // for (int i = 0; i < primeTable.size(); i++) {
      // printf("2^%d-1: \r\n", primeTable[i]);
      tirado4b(exponent, debugLevel);

      break;
    }
  }
}

// 2, 3, 5, 7, 11, 13, 17, 19, 23, 29. 31, 37, 41, 43, 47, 53, 59, 61, 67,