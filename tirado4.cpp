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
  mpz_class pow2, pow2b;
  mpz_class modK;
  mpz_class dif;
  int exp;
  exp = 1;
  pow2b = 0;

  mpz_ui_pow_ui(value.get_mpz_t(), 2, exponent);
  value = value - 2;

  while (true) {
    mpz_ui_pow_ui(pow2.get_mpz_t(), 2, exp);
    dif = value - pow2b;
    k = value / pow2;

    gmp_printf("%Zd - %Zd = %Zd; %Zd / %Zd = %Zd = (2^%d - 1)\r\n",
               value.get_mpz_t(), pow2b.get_mpz_t(), dif.get_mpz_t(),
               dif.get_mpz_t(), pow2.get_mpz_t(), k.get_mpz_t(),
               (exponent - exp));

    if (k == 1)
      break;
    value = value - pow2b;
    pow2b = pow2;
    exp++;
  }
}

void tirado4c(int exponent, int debugLevel) {

  mpz_class value, value2, oddFactor, mod;
  mpz_ui_pow_ui(value.get_mpz_t(), 2, exponent);
  value = value - 2;
  int exp = 0;
  int base = 2;
  vector<factor> factors, factors2;

  while (true) {
    value2 = value;
    base = 2;
    while (true) {
      factor f;
      f.base = base;
      while (true) {
        mod = value2 % base;
        if (mod == 0) {
          value2 = value2 / base;
          f.exp++;
        } else {
          base++;
          break;
        }
      }
      if (f.exp > 0) {
        factors.push_back(f);
      }
      if (value2 == 1)
        break;
    }

    value--;
    if (value == 0)
      break;
  }

  string fs = "";
  int pos = -1;
  int i, j;

  sort(factors.begin(), factors.end(), compareFactors);

  for (i = 0; i < factors.size(); i++) {
    pos = -1;
    for (j = 0; j < factors2.size(); j++) {
      if (factors2[j].base == factors[i].base)
        pos = j;
    }
    if (pos < 0) {
      factors2.push_back(factors[i]);
    } else {
      factors2[pos].exp += factors[i].exp;
    }
  }

  sort(factors2.begin(), factors2.end(), compareFactors);

  for (factor f : factors2) {
    fs = fs + f.base.get_str() + "^" + f.exp.get_str() + "\r\n";
  }

  cout << fs << endl;
  cout << endl;
}

void tirado4d(int exponent, int debugLevel) {

  mpz_class value, value2, oddFactor, mod;
  mpz_ui_pow_ui(value.get_mpz_t(), 2, exponent);
  value = value - 2;
  int exp = 0;
  int base = 2;
  vector<factor> factors, factors2;

  while (true) {
    value2 = value;
    base = 2;
    while (true) {
      factor f;
      f.base = base;
      while (true) {
        mod = value2 % base;
        if (mod == 0) {
          value2 = value2 / base;
          f.exp++;
        } else {
          base++;
          break;
        }
      }
      if (f.exp > 0) {
        factors.push_back(f);
      }
      if (value2 == 1)
        break;
    }

    value--;
    if (value == 0)
      break;
  }

  string fs = "";
  int pos = -1;
  int i, j;

  sort(factors.begin(), factors.end(), compareFactors);

  for (i = 0; i < factors.size(); i++) {
    pos = -1;
    for (j = 0; j < factors2.size(); j++) {
      if (factors2[j].base == factors[i].base)
        pos = j;
    }
    if (pos < 0) {
      factors2.push_back(factors[i]);
    } else {
      factors2[pos].exp += factors[i].exp;
    }
  }

  sort(factors2.begin(), factors2.end(), compareFactors);

  for (factor f : factors2) {
    fs = fs + f.base.get_str() + "^" + f.exp.get_str() + "\r\n";
  }

  cout << fs << endl;
  cout << endl;
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

  argHdl.add(argument(5, (char *)"b", (char *)"aldo 2 test",
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

    case 5:
      argHdl.pvalue(&exponent);
      // for (int i = 0; i < primeTable.size(); i++) {
      // printf("2^%d-1: \r\n", primeTable[i]);
      tirado4c(exponent, debugLevel);

      break;
    }
  }

  mpz_class a, b, c, d, r;

  a = (semiFactorial(29) * semiFactorial(7) * (15 * 13 * 11 * 9 * 7 * 3)) + 1;
  b = 31;
  c = a / b;
  d = a % b;
  mpz_mod(r.get_mpz_t(), a.get_mpz_t(), b.get_mpz_t());

  gmp_printf("a=%Zd \r\n b=%Zd \r\n c=%Zd  \r\n d=%Zd \r\n r=%Zd", a.get_mpz_t(),
             b.get_mpz_t(), c.get_mpz_t(), d.get_mpz_t(), r.get_mpz_t());
  cout << endl;
}

// 2, 3, 5, 7, 11, 13, 17, 19, 23, 29. 31, 37, 41, 43, 47, 53, 59, 61, 67,