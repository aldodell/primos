#include "tirado4.h"

/** Descompone un número de mersenne en sus doble facotirales */
void tirado4a(int exponent, int debugLevel) {

  vector<factor> factors;
  vector<mpz_class> factorials;

  mpz_class evenN;

  mpz_class k;
  mpz_class modK;
  mpz_class exp = 1;
  mpz_class pow2;
  mpz_class two = 2;
  bool done = false;

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

/** Calcula el producto de doble factorial para un número de mersene dado.*/
void tirado4e(int exponent, int debugLevel) {

  mpz_class a, b, c, d, r, q;

  mpz_ui_pow_ui(a.get_mpz_t(), 2, exponent);
  a = a - 3;
  b = ((a + 1) / 2) - 2;
  c = (((b + 2) + 1) / 2) - 1;
  d = a + 2;

  r = doubleFactorial(a) * doubleFactorial(b) * doubleFactorial(c);

  while (true) {
    c = ((c + 1) / 2) - 1;
    r = r * doubleFactorial(c);
    if (c < 4)
      break;
  }

  mpz_mod(q.get_mpz_t(), r.get_mpz_t(), d.get_mpz_t());
  gmp_printf("r=%Zd \r\n d=%Zd \r\n q=%Zd \r\n", r.get_mpz_t(), d.get_mpz_t(),
             q.get_mpz_t());
}

/** Calcula los argumentos (Tirado) en el número de Mersenne */
void tirado4f(int exponent, int debugLevel) {

  // 11, 23, 29, 37,
  vector<int> exponents{41, 43, 47, 53, 59};
  mpz_class mersenne, f1, f2;

  primeTester tester(100);
  bigGearsFactorizer bgf(&tester);
  bigGearsFactorizer bgf2(&tester);

  for (int i = 0; i < exponents.size(); i++) {
    int exp = exponents[i];
    mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, exp);
    mersenne--;
    bgf.find(mersenne);
    cout << "2^" << exp << "-1: " << bgf.toString() << endl;

    for (int j = 0; j < bgf.factors.size(); j++) {
      mpz_class f1 = bgf.factors[j];
      f2 = (f1 - 1) / 2;
      bgf2.find(f2);
      cout << "\t Argument of (" << f1 << ") =: " << f2 << " = "
           << bgf2.toString() << endl;
      bgf2.clear();
    }
    bgf.clear();
  }
}

/*+ Buscar en los argumentos de Tirado el algún factor que sea igual al
exponente*/

void tirado4h(int exponent, int debugLevel) {
  mpz_class mersenne, n, m, pivot, argument, root;
  bigHalfGearFactorizer bhg;
  int oddExp = 0;

  // calculamos el mersenne
  mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, exponent);
  mersenne--;

  // Obtenemos la raíz cuadrada de mersenne
  mpz_sqrt(root.get_mpz_t(), mersenne.get_mpz_t());

  pivot = root;
  // if pivot is even... convert to odd
  if (mpz_tstbit(pivot.get_mpz_t(), 0) == 0) {
    pivot--;
  }

  // Imprimimos:
  gmp_printf("2^%d - 1 = %Zd\r\n", exponent, mersenne.get_mpz_t());

  while (true) {

    argument = (pivot - 1) / 2;
    bhg.clear();
    bhg.find(argument);
    gmp_printf("\t 2m+1 form: %Zd\r\n", argument.get_mpz_t());
    gmp_printf("\t\t %s\r\n", bhg.toString().c_str());
    pivot -= 2;
    if (pivot == 3)
      break;
  }
  cout << endl;
  /*
    argument = (pivot - 1) / 2;
      bhg.clear();
      bhg.find(argument);

      pivot = (pivot * 2) + 1;
      */
  /*
    // Para calcular Wilson, restamos 1.
    n = mersenne - 1;

    // Filtramos el 2^n
    while (mpz_tstbit(n.get_mpz_t(), 0) == 0) {
      n /= 2;
      oddExp++;
    }

    // Obtenemos la raíz cuadrada de mersenne
    mpz_sqrt(root.get_mpz_t(), mersenne.get_mpz_t());

    // Si la raíz es par le restamos 1:
    if (mpz_tstbit(root.get_mpz_t(), 0) == 0) {
      root--;
    }
  */
}

/*+ Buscar en los argumentos de Tirado el algún factor que sea igual al
exponente

2^19 - 1 = 524287
Square root = 724

pivot=647
argument(2m+1): 323
DIVISIBLE BY 19 => 323/19 = 17

En este caso se calcula el primer doble factorial=2^p-1-1-1;
Luego se va decrementando hasta 3
en cada ciclo se pasa a la forma 2m+1 (Tirado)
y se evalúa solo los doble factoriales primos
*/
void tirado4i(int exponent, int debugLevel) {

  mpz_class mersenne, n, m, pivot, argument, root, mod, div;
  bigHalfGearFactorizer bhg;

  // calculamos el mersenne
  mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, exponent);
  mersenne--;

  // Obtenemos la raíz cuadrada de mersenne
  mpz_sqrt(root.get_mpz_t(), mersenne.get_mpz_t());

  pivot = root;

  // if pivot is even... convert to odd
  if (mpz_tstbit(pivot.get_mpz_t(), 0) == 0) {
    pivot++;
  }

  // Imprimimos:
  gmp_printf("2^%d - 1 = %Zd\r\n", exponent, mersenne.get_mpz_t());
  gmp_printf("Square root = %Zd\r\n", root.get_mpz_t());

  while (true) {
    if (mpz_probab_prime_p(pivot.get_mpz_t(), 50) > 0) {
      argument = (pivot - 1) / 2;
      mpz_mod_ui(mod.get_mpz_t(), argument.get_mpz_t(), exponent);
      if (mod == 0) {
        gmp_printf("\r\npivot=2m+1=%Zd\r\n", pivot.get_mpz_t());
        gmp_printf("m=%Zd\r\n", argument.get_mpz_t());
        div = argument / exponent;
        gmp_printf("DIVISIBLE BY %d => %Zd/%d = %Zd\r\n", exponent,
                   argument.get_mpz_t(), exponent, div.get_mpz_t());
      }
    }
    pivot -= 2;
    if (pivot == 3)
      break;
  }
  cout << endl;
}

void tirado4j(int exponent, int debugLevel) {

  mpz_class mersenne, n, m, pivot, argument, root, mod, div;
  bigHalfGearFactorizer bhg;

  // get  mersenne
  mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, exponent);
  mersenne--;

  // get square root of mersenne
  mpz_sqrt(root.get_mpz_t(), mersenne.get_mpz_t());

  // assign first value to pivot, Mersenne sqare root
  pivot = root;

  // if pivot is even... convert to odd
  if (mpz_tstbit(pivot.get_mpz_t(), 0) == 0) {
    pivot++;
  }

  // Print label:
  gmp_printf("2^%d - 1 = %Zd\r\n", exponent, mersenne.get_mpz_t());
  gmp_printf("Square root = %Zd\r\n", root.get_mpz_t());

  while (true) {
    // 2m+1
    argument = (pivot - 1) / 2;

    // Is argument prime? (probabilistic test for velocity)
    if (mpz_probab_prime_p(argument.get_mpz_t(), 50) > 0) {

      // Get module: argument % exponent
      mpz_mod_ui(mod.get_mpz_t(), argument.get_mpz_t(), exponent);

      // If module = 0, so argument is divisible by exponent
      if (mod == 0) {
        gmp_printf("\r\npivot=%Zd\r\n", pivot.get_mpz_t());
        gmp_printf("argument(2m+1): %Zd\r\n", argument.get_mpz_t());
        div = argument / exponent;
        gmp_printf("DIVISIBLE BY %d => %Zd/%d = %Zd\r\n", exponent,
                   argument.get_mpz_t(), exponent, div.get_mpz_t());
      }
    }
    // decrement pivot
    pivot -= 2;

    // exit condition
    if (pivot == 3)
      break;
  }
  cout << endl;
}

void tirado4k(int exponent, int debugLevel) {

  mpz_class mersenne, n, m, pivot, argument, root, mod, div;
  bigHalfGearFactorizer bhg;

  // calculamos el mersenne
  mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, exponent);
  mersenne--;

  // Obtenemos la raíz cuadrada de mersenne
  mpz_sqrt(root.get_mpz_t(), mersenne.get_mpz_t());

  pivot = root;
  // if pivot is even... convert to odd
  if (mpz_tstbit(pivot.get_mpz_t(), 0) == 0) {
    pivot--;
  }

  // Imprimimos:
  gmp_printf("2^%d - 1 = %Zd\r\n", exponent, mersenne.get_mpz_t());
  gmp_printf("Square root = %Zd\r\n", root.get_mpz_t());

  while (true) {
    mpz_mod_ui(mod.get_mpz_t(), pivot.get_mpz_t(), exponent);
    if (mod == 0) {
      gmp_printf("\r\npivot=%Zd\r\n", pivot.get_mpz_t());
      // gmp_printf("argument(2m+1): %Zd\r\n", argument.get_mpz_t());
      div = pivot / exponent;
      gmp_printf("DIVISIBLE BY %d => %Zd/%d = %Zd\r\n", exponent,
                 pivot.get_mpz_t(), exponent, div.get_mpz_t());
    }

    pivot -= 2;
    if (pivot == 3)
      break;
  }
  cout << endl;
}

void tirado4l(int exponent, int debugLevel) {

  mpz_class mersenne, n, m, pivot, argument, root, mod, div;
  bigHalfGearFactorizer bhg;

  // calculamos el mersenne
  mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, exponent);
  mersenne--;

  // Obtenemos la raíz cuadrada de mersenne
  mpz_sqrt(root.get_mpz_t(), mersenne.get_mpz_t());

  pivot = root;

  // if pivot is even... convert to odd
  // if (mpz_tstbit(pivot.get_mpz_t(), 0) == 0) {
  //  pivot++;
  // }

  // Le quito la paridad si la tiene
  while (mpz_tstbit(pivot.get_mpz_t(), 0) == 0) {
    pivot /= 2;
  }

  // Imprimimos:
  gmp_printf("2^%d - 1 = %Zd\r\n", exponent, mersenne.get_mpz_t());
  gmp_printf("Square root = %Zd\r\n", root.get_mpz_t());

  while (true) {
    // if (mpz_probab_prime_p(pivot.get_mpz_t(), 50) > 0) {
    argument = (pivot - 1) / 2;
    mpz_mod_ui(mod.get_mpz_t(), argument.get_mpz_t(), exponent);
    if (mod == 0) {
      gmp_printf("\r\npivot=%Zd\r\n", pivot.get_mpz_t());
      gmp_printf("argument(2m+1): %Zd\r\n", argument.get_mpz_t());
      div = argument / exponent;
      gmp_printf("DIVISIBLE BY %d => %Zd/%d = %Zd\r\n", exponent,
                 argument.get_mpz_t(), exponent, div.get_mpz_t());
    }
    break; // Sólo obtenemos el primer doble factorial primo menor que la raíz
           // cuadrada de m
    //}
    pivot -= 2;
    if (pivot == 3)
      break;
  }
  cout << endl;
}

void tirado4m(int exponent, int debugLevel) {

  kdProcessSpin spin;
  kdTimer timer;

  mpz_class mersenne, root, k, factor, mod;

  timer.start();

  // Get Mersenne
  mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, exponent);
  mersenne--;

  // get root
  mpz_sqrt(root.get_mpz_t(), mersenne.get_mpz_t());
  k = 1;
  while (true) {
    factor = (k * exponent) + 1;
    mpz_mod(mod.get_mpz_t(), mersenne.get_mpz_t(), factor.get_mpz_t());
    if (mod == 0) {
      gmp_printf("isn't prime. Has %Zd factor\n", factor.get_mpz_t());
      break;
    }
    if (factor > root) {
      printf("is prime\n");
      break;
    }
    k++;
  }

  printf("Time elapsed: %f\n", timer.stop());
}

void tirado4n(int exponent, int debugLevel) {

  kdProcessSpin spin;
  kdTimer timer;
  kdProcessBenchmark benchmark;

  mpz_class mersenne, root, rootMinusOne, k, k2, factor, border, mod, cycles,
      twoBase, exp;

  twoBase = 2;
  exp = exponent;

  // This factor is 2^n * exponent in order to improve calc velocity
  // int twoFactor[]{2 * exponent,  4 * exponent,  8 * exponent,  16 * exponent,
  //              32 * exponent, 64 * exponent, 128 * exponent};
  // int twoFactorIndex;
  bool process = true;

  timer.start();
  spin.cyclesForStep = 100000000;
  spin.reset();
  benchmark.cyclesForStep = 20000000;

  // Get Mersenne
  mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, exponent);
  mersenne--;
  gmp_printf("Processing 2^%d-1\n", exponent);

  int isExpPrime = mpz_probab_prime_p(exp.get_mpz_t(), 50);
  if (isExpPrime < 2) {
    gmp_printf("Warning! 2^%d-1 This program requires \n an prime exponent to "
               "generate prime "
               "numbers. \n Ambigous results will return.\n",
               exponent);
  }

  /** Probabilistic test. Spend much time
  int prob = mpz_probab_prime_p(mersenne.get_mpz_t(), 15);
  switch (prob) {
  case 0:
    gmp_printf("Processing 2^%d-1 isn't prime by prob test\n", exponent);
    break;
  case 1:
    gmp_printf("Processing 2^%d-1 could be prime by prob test\n", exponent);
    break;
  case 2:
    gmp_printf("Processing 2^%d-1 is prime by prob test\n", exponent);
    break;

  default:
    break;
  }
  */

  // get root
  mpz_sqrt(root.get_mpz_t(), mersenne.get_mpz_t());
  // rootMinusOne = root - 1;
  k = 1;
  // border = root / (2 * exponent);
  k2 = 2 * exponent;

  benchmark.start();
  while (process) {
    factor = k * k2 + 1;
    if (root < factor) {
      gmp_printf("is prime. k = %Zd\n", k.get_mpz_t());
      process = false;
      break;
    }
    // for (twoFactorIndex = 0; twoFactorIndex < 4; twoFactorIndex++) {
    // factor = (twoFactor[twoFactorIndex] * k) + 1;
    // mpz_mod(mod.get_mpz_t(), mersenne.get_mpz_t(), factor.get_mpz_t());
    mpz_powm(mod.get_mpz_t(), twoBase.get_mpz_t(), exp.get_mpz_t(),
             factor.get_mpz_t());
    if (mod == 1) {
      gmp_printf("isn't prime. Has %Zd factor\n", factor.get_mpz_t());
      process = false;
      break;
    }
    //}
    k += 1;
    // spin.show();
    benchmark.tick();
  }

  gmp_printf("Time elapsed: %f, k=%Zd\n", timer.stop(), k.get_mpz_t());
}

void tirado4o(int exponent, int debugLevel) {

  mpz_class prime;
  prime = 2;
  for (int i = 0; i < 30; i++) {
    mpz_nextprime(prime.get_mpz_t(), prime.get_mpz_t());
    tirado4n(prime.get_ui(), 0);
  }
}

void tirado4p(int exponent, int debugLevel) {
  /**
   * 7=2 (3)+1
3=2 (1)+1
      .
      .
13=2 (6)+1
6=2×3 y 3=2 (1)+1
       .
       .
19=2 (9)+1
9=3^2
*/

  unsigned int mersenneExponents[]{
      2,        3,        5,        7,        13,       17,       19,
      31,       61,       89,       107,      127,      521,      607,
      1279,     2203,     2281,     3217,     4253,     4423,     9689,
      9941,     11213,    19937,    21701,    23209,    44497,    86243,
      110503,   132049,   216091,   756839,   859433,   1257787,  1398269,
      2976221,  3021377,  6972593,  13466917, 20996011, 24036583, 25964951,
      30402457, 32582657, 37156667, 42643801, 43112609};

  unsigned int p = exponent;
  unsigned a, b, mod;

  for (int i = 1; i < 47; i++) {
    p = mersenneExponents[i];
    printf("p=%d\n", p);
    a = 2;
    while (true) {
      if (p == 2)
        break;
      mod = (p - 1) % a;
      if (mod == 0) {
        b = (p - 1) / a;
        printf("\t%d=%d*%d + 1\n", p, a, b);
        p = b;
        a = 1;
      }
      if (b == 1)
        break;
      a++;
    }
    printf("\n");
  }
}

/** Calcula el tiempo de cálculo*/
void tirado4q(int exponent, int speed, int debugLevel) {

  mpz_class mersenne, root, kmax, days;

  // calcular mersenne
  mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, exponent);
  mersenne--;

  // calcular raiz
  mpz_sqrt(root.get_mpz_t(), mersenne.get_mpz_t());

  // calcular kmax
  kmax = (root - 1) / (2 * exponent);

  days = (kmax / speed) / (3600 * 24);
  gmp_printf("Days to calculate: %Zd k:%Zd speed: %d\n", days.get_mpz_t(),
             kmax.get_mpz_t(), speed);
}

/**
 * Distribuye los exponentes p en 2^p-1 que generan números primos
 * en las formas 4k+1 y 4k+3
 * */
void tirado4t(int exponent, int debugLevel) {

  unsigned int mersenneExponents[]{
      2,        3,        5,        7,        13,       17,       19,
      31,       61,       89,       107,      127,      521,      607,
      1279,     2203,     2281,     3217,     4253,     4423,     9689,
      9941,     11213,    19937,    21701,    23209,    44497,    86243,
      110503,   132049,   216091,   756839,   859433,   1257787,  1398269,
      2976221,  3021377,  6972593,  13466917, 20996011, 24036583, 25964951,
      30402457, 32582657, 37156667, 42643801, 43112609, 57885161, 74207281,
      77232917, 82589933};

  vector<int> p4k1, p4k3, p4km1, p4km3;
  int t;

  for (int i = 0; i < 51; i++) {
    t = (mersenneExponents[i] - 1) % 4;
    if (t == 0) {
      p4k1.push_back(mersenneExponents[i]);
    }

    t = (mersenneExponents[i] + 1) % 4;
    if (t == 0) {
      p4km1.push_back(mersenneExponents[i]);
    }

    t = (mersenneExponents[i] - 3) % 4;
    if (t == 0) {
      p4k3.push_back(mersenneExponents[i]);
    }

    t = (mersenneExponents[i] + 3) % 4;
    if (t == 0) {
      p4km3.push_back(mersenneExponents[i]);
    }
  }

  printf("*4k+1:*\n");
  for (int i = 0; i < p4k1.size(); i++) {
    int k = (p4k1[i] - 1) / 4;
    printf("%d : %d\n", p4k1[i], k);
  }

  printf("Size: %lu\n\r\n\r", p4k1.size());

  printf("-------------\n*4k-1:*\n");
  for (int i = 0; i < p4km1.size(); i++) {
    int k = (p4km1[i] + 1) / 4;
    printf("%d : %d\n", p4km1[i], k);
  }
  printf("Size: %lu\n\r\n\r", p4km1.size());

  printf("-------------\n*4k+3:*\n");
  for (int i = 0; i < p4k3.size(); i++) {
    int k = (p4k3[i] - 3) / 4;
    printf("%d : %d\n", p4k3[i], k);
  }
  printf("Size: %lu\n\r\n\r", p4k3.size());

  printf("-------------\n*4k-3:*\n");
  for (int i = 0; i < p4km3.size(); i++) {
    int k = (p4km3[i] + 3) / 4;
    printf("%d : %d\n", p4km3[i], k);
  }
  printf("Size: %lu\n\r\n\r", p4km3.size());
}

/**
 * Atomización de exponentes primos de mersenne
 * */
void tirado4u(int exponent, int debugLevel) {
  unsigned int mersenneExponents[]{
      2,        3,        5,        7,        13,       17,       19,
      31,       61,       89,       107,      127,      521,      607,
      1279,     2203,     2281,     3217,     4253,     4423,     9689,
      9941,     11213,    19937,    21701,    23209,    44497,    86243,
      110503,   132049,   216091,   756839,   859433,   1257787,  1398269,
      2976221,  3021377,  6972593,  13466917, 20996011, 24036583, 25964951,
      30402457, 32582657, 37156667, 42643801, 43112609, 57885161, 74207281,
      77232917, 82589933};
  int i, p, q, mod, mod1, mod3;
  mpz_class gp;

  bigHalfGearFactorizer gf;
  bool isPrimeMersenne;

  i = 0;
  p = 2;
  gp = 2;
  printf("*_p_=%d*\n", p);

  while (true) {

    mod1 = (p - 1) % 4;
    mod3 = (p - 3) % 4;

    if (mod1 == 0) {
      q = (p - 1) / 4;
      printf("\t%d=4(%d)+1\n", p, q);
      p = q;
    } else if (mod3 == 0) {
      q = (p - 3) / 4;
      printf("\t%d=4(%d)+3\n", p, q);
      p = q;
    } else {
      if (p > 3) {
        gf.find(p);
        printf("\t%d=%s\n", p, gf.toString().c_str());
        gf.clear();
        printf("\tfootprint=%d\n", p / 2);
      } else {
        printf("\tfootprint=%d\n", p / 2);
      }

      i++;
      if (i == 1000)
        break;

      mpz_nextprime(gp.get_mpz_t(), gp.get_mpz_t());
      p = gp.get_ui();
      isPrimeMersenne =
          std::find(std::begin(mersenneExponents), std::end(mersenneExponents),
                    p) != std::end(mersenneExponents);

      printf("\n*_p_=%d* ", p);
      if (isPrimeMersenne) {
        printf("*Is mersenne prime*\n");
      } else {
        printf("\n");
      }
    }
  }
}

/**
 * Atomización de exponentes primos de mersenne, comparando su comportamiento
 * al cambiar 4k+1 por 4k-3 y 4k+3 por k4-1
 * */
void tirado4v(int exponent, int debugLevel) {
  unsigned int mersenneExponents[]{
      2,        3,        5,        7,        13,       17,       19,
      31,       61,       89,       107,      127,      521,      607,
      1279,     2203,     2281,     3217,     4253,     4423,     9689,
      9941,     11213,    19937,    21701,    23209,    44497,    86243,
      110503,   132049,   216091,   756839,   859433,   1257787,  1398269,
      2976221,  3021377,  6972593,  13466917, 20996011, 24036583, 25964951,
      30402457, 32582657, 37156667, 42643801, 43112609, 57885161, 74207281,
      77232917, 82589933};

  int i;
  int mod4k1;  // 4k+1
  int mod4k3;  // 4k+3
  int mod4km1; // 4k-1
  int mod4km3; // 4k+1
  int p;
  int ka;
  int kb;

  for (i = 0; i < 51; i++) {
    p = mersenneExponents[i];

    printf("*p=%d*\n", p);

    while (true) {
      mod4k1 = (p - 1) % 4;
      mod4k3 = (p - 3) % 4;

      if (mod4k1 == 0) {
        ka = (p - 1) / 4;
        kb = (p + 3) / 4;
        printf("%d = 4(%d)+1 = 4(%d)-3\n", p, ka, kb);
        p = (p - 1) / 4;
      } else if (mod4k3 == 0) {
        ka = (p - 3) / 4;
        kb = (p + 1) / 4;
        printf("%d = 4(%d)+3 = 4(%d)-1\n", p, ka, kb);
        p = (p - 3) / 4;
      } else {
        printf("\n");
        break;
      }
    }

    p = mersenneExponents[i];

    while (true) {
      mod4km1 = (p + 1) % 4;
      mod4km3 = (p + 3) % 4;
      if (mod4km1 == 0) {
        ka = (p + 1) / 4;
        kb = (p - 3) / 4;
        printf("%d = 4(%d)-1 = 4(%d)+3\n", p, ka, kb);
        p = (p + 1) / 4;
      } else if (mod4km3 == 0) {
        ka = (p + 3) / 4;
        kb = (p - 1) / 4;
        printf("%d = 4(%d)-3 = 4(%d)+1\n", p, ka, kb);
        p = (p + 3) / 4;
        if (p == 1) {
          printf("\n");
          break;
        }

      } else {
        printf("\n");
        break;
      }
    }
  }
}

/** Toma los números de Mersenne (excluyendo lo que se saben generan primos)
 * para evaluar sus factores en la forma: 2pk+1
 * */

void tirado4w(int exponent, int debugLevel) {
  unsigned int mersenneExponents[]{
      2,        3,        5,        7,        13,       17,       19,
      31,       61,       89,       107,      127,      521,      607,
      1279,     2203,     2281,     3217,     4253,     4423,     9689,
      9941,     11213,    19937,    21701,    23209,    44497,    86243,
      110503,   132049,   216091,   756839,   859433,   1257787,  1398269,
      2976221,  3021377,  6972593,  13466917, 20996011, 24036583, 25964951,
      30402457, 32582657, 37156667, 42643801, 43112609, 57885161, 74207281,
      77232917, 82589933};

  mpz_class p, p2, k, f, r, m, mod, TWO, fx;
  int i;
  p = 2;
  TWO = 2;
  bool isPrimeMersenne;

  for (i = 0; i < 100; i++) {
    mpz_nextprime(p.get_mpz_t(), p.get_mpz_t());

    isPrimeMersenne =
        std::find(std::begin(mersenneExponents), std::end(mersenneExponents),
                  p.get_ui()) != std::end(mersenneExponents);

    if (!isPrimeMersenne) {
      mpz_ui_pow_ui(m.get_mpz_t(), 2, p.get_ui());
      m--;
      gmp_printf("*2^%Zd-1*\n", p.get_mpz_t());
      mpz_sqrt(r.get_mpz_t(), m.get_mpz_t());

      p2 = 2 * p;
      k = 1;
      while (true) {
        while (true) {
          f = p2 * k + 1;
          mpz_mod(mod.get_mpz_t(), m.get_mpz_t(), f.get_mpz_t());
          if (mod.get_ui() == 0) {
            m = m / f;

            k++;
            break;
          }
          k++;
        }
        gmp_printf("\t%Zd = 2 x %Zd x %Zd + 1\n", f.get_mpz_t(), p.get_mpz_t(),
                   k.get_mpz_t());
        if (m.get_ui() == 1) {
          break;
        }
      }
      printf("\n");
    }
  }
}

void tirado4x(int exponent, int debugLevel) {
  mpz_class m, mt, q, r;
  int n;

  mpz_ui_pow_ui(m.get_mpz_t(), 2, exponent);
  mpz_sub_ui(mt.get_mpz_t(), m.get_mpz_t(), 2);
  n = mpz_divisible_ui_p(mt.get_mpz_t(), exponent);

  gmp_printf("n=%d, r=%Zd\n", n, r.get_mpz_t());
}

void atomizer(mpz_class init) {
  mpz_class j, k;
  k = init;
  bigHalfGearFactorizer gf;

  printf("<ul>");
  gmp_printf("<li>First form:<ul>\n");
  while (true) {
    if (k == 1)
      break;
    // ¿Es de la forma 4k+1?
    if ((k - 1) % 4 == 0) {
      j = k;
      k = (k - 1) / 4;
      gf.clear();
      gf.find(k);
      gmp_printf("<li>%Zd => 4k+1 => k=%Zd {%s}</li>\n", j.get_mpz_t(),
                 k.get_mpz_t(), gf.toString().c_str());
    } else // ¿Es de la forma 4k+3?
        if ((k - 3) % 4 == 0) {
      j = k;
      k = (k - 1) / 4;
      gf.clear();
      gf.find(k);
      gmp_printf("<li>%Zd => 4k+3 => k=%Zd {%s}</li>\n", j.get_mpz_t(),
                 k.get_mpz_t(), gf.toString().c_str());
    } else if ((k + 1) % 4 == 0) {
      j = k;
      k = (k + 1) / 4;
      gf.clear();
      gf.find(k);
      gmp_printf("<li>%Zd => 4k-1 => k=%Zd {%s}</li>\n", j.get_mpz_t(),
                 k.get_mpz_t(), gf.toString().c_str());
    } else // ¿Es de la forma 4k-1?
        if ((k + 3) % 4 == 0) {
      j = k;
      k = (k + 1) / 4;
      gf.clear();
      gf.find(k);
      gmp_printf("<li>%Zd => 4k-3 => k=%Zd {%s}</li>\n", j.get_mpz_t(),
                 k.get_mpz_t(), gf.toString().c_str());
    } else {
      break;
    }
  }

  gmp_printf("\n</ul></li><li>Second form:<ul>\n");
  k = init;
  while (true) {

    if (k == 1)
      break;
    // ¿Es de la forma 4k-1?
    if ((k + 1) % 4 == 0) {
      j = k;
      k = (k + 1) / 4;
      gf.clear();
      gf.find(k);
      gmp_printf("<li>%Zd => 4k-1 => k=%Zd {%s}</li>\n", j.get_mpz_t(),
                 k.get_mpz_t(), gf.toString().c_str());
      // ¿Es de la forma 4k-1?
    } else if ((k + 3) % 4 == 0) {
      j = k;
      k = (k + 3) / 4;
      gf.clear();
      gf.find(k);
      gmp_printf("<li>%Zd => 4k-3 => k=%Zd {%s}</li>\n", j.get_mpz_t(),
                 k.get_mpz_t(), gf.toString().c_str());
    } else if ((k - 1) % 4 == 0) {
      j = k;
      k = (k - 1) / 4;
      gf.clear();
      gf.find(k);
      gmp_printf("<li>%Zd => 4k+1 => k=%Zd {%s}</li>\n", j.get_mpz_t(),
                 k.get_mpz_t(), gf.toString().c_str());
    } else // ¿Es de la forma 4k+3?
        if ((k - 3) % 4 == 0) {
      j = k;
      k = (k - 3) / 4;
      gf.clear();
      gf.find(k);
      gmp_printf("<li>%Zd => 4k+3 => k=%Zd {%s}</li>\n", j.get_mpz_t(),
                 k.get_mpz_t(), gf.toString().c_str());
    } else {
      break;
    }
  }
  printf("</ul></ul></li></ul>");
}

/**Análisis de cada número de Mersenne*/
void tirado4y(mpz_class exponent, int debugLevel) {

  unsigned int mersenneExponents[]{
      2,        3,        5,        7,        13,       17,       19,
      31,       61,       89,       107,      127,      521,      607,
      1279,     2203,     2281,     3217,     4253,     4423,     9689,
      9941,     11213,    19937,    21701,    23209,    44497,    86243,
      110503,   132049,   216091,   756839,   859433,   1257787,  1398269,
      2976221,  3021377,  6972593,  13466917, 20996011, 24036583, 25964951,
      30402457, 32582657, 37156667, 42643801, 43112609, 57885161, 74207281,
      77232917, 82589933};

  mpz_class mersenne, m0, j, k, xp, xm, exp;
  int n, digits, lastDigit;
  bigHalfGearFactorizer gf;
  char *lastTenDigits;

  for (int z = 0; z < 9; z++) {
    exponent = mersenneExponents[z];

    // Obtenemos Mersenne
    mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, exponent.get_ui());
    mersenne--;

    // printf("%s\n", string(80, '*').c_str());
    gmp_printf("<hr><h1>Analyzing: 2^%Zd-1</h1>\n", exponent.get_mpz_t());

    m0 = mersenne;

    /**
     * Data about Mersenne M
     * */
    digits = ((log(2) / log(10)) * exponent.get_ui()) + 1;
    lastDigit = (exponent / 2) % 2 == 0 ? 1 : 7;
    printf("\n<h2>Mersenne analysis:</h2>\n");
    printf("<ul>");
    printf("<li>Digits: %d</li>\n<li>Last digit: ...%d</li>\n\n", digits,
           lastDigit);
    printf("</ul>");
    /**
     * Data about exponent p on 2^p-1
     * */

    // Calculamos los exponentes

    printf("\n<h2>Exponent analysis: Is 4k+1, 4k+3, 4k-1, 4k-3 form?</h2>\n");
    atomizer(exponent);
    /**
     * Calcular Xp: p = 2Xp+1
     * */

    xp = (exponent - 1) / 2;

    gmp_printf("\n\t<h3>Analysis of Xp: p = 2*Xp + 1 => Xp=%Zd</h3>\n",
               xp.get_mpz_t());
    atomizer(xp);
    gf.clear();
    gf.find(xp.get_ui());
    gmp_printf("\n\t<p>Factors of Xp{%Zd} = %s</p>\n", xp.get_mpz_t(),
               gf.toString().c_str());

    /** Deep analysis of Mersenne */
    printf("\n<h2>Deep Mersenne analysis</h2>\n");

    if (m0.get_str().length() > 10) {
      lastTenDigits = (char *)mersenne.get_str().substr(digits - 10).c_str();
    } else {
      lastTenDigits = (char *)mersenne.get_str().c_str();
    }

    printf("<p>Last ten digits:%s</p>\n", (char *)lastTenDigits);

    /** Calculate Xm: 2^p-1 = 2pXm+1
     * */
    xm = (m0 - 1) / (2 * exponent);
    if (xm.get_str().length() > 10) {
      lastTenDigits = (char *)xm.get_str().substr(digits - 12).c_str();
    } else {
      lastTenDigits = (char *)xm.get_str().c_str();
    }
    gmp_printf("\n\t<h3>Analysis of Xm: M = 2*p*Xm + 1 => Xm=%s [last ten "
               "digits]</h3>\n",
               lastTenDigits);

    gf.clear();
    gf.find(xm);
    gmp_printf("\n\t<p>Factors of Xm = %s</p>\n", gf.toString().c_str());

    atomizer(xm);
  }
}

string type4k(mpz_class n) {
  string r;
  if ((n - 1) % 4 == 0) {
    r = "4k+1";
  } else if ((n - 3) % 4 == 0) {
    r = "4k+3";
  } else {
    r = "";
  }
  return r;
}

/**Análisis de cada número de Mersenne*/
void tirado4z(mpz_class exponent, int debugLevel) {

  int i;

  mpz_class p = 1;
  mpz_class mersenne;
  mpz_class Xp, Xm;
  bigHalfGearFactorizer bf;
  string XpFactors, XmFactors;

  printf("\\documentclass{article}\r\n"
         "%% Definimos el título \r\n"
         "\\title{Título del documento} \r\n"
         "\\begin{document} \r\n"
         "\\maketitle %% Creamos el título \r\n"
         "\\begin{tabular}{c | c | c | c} \r\n");

  /** Send html table codes */
  printf("M & 4pk+? & Xp=(p-1)/2 & Xm=(M-1)/(2p) \\\\ \\hline \r\n");

  for (i = 0; i < 33; i++) { // Recorren los números primos
    // Take next prime: exponent
    mpz_nextprime(p.get_mpz_t(), p.get_mpz_t());
    mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, p.get_ui());
    mersenne--;
    Xp = (p - 1) / 2;
    Xm = (mersenne - 1) / (2 * p);

    bf.clear();
    bf.find(Xp);
    XpFactors = bf.toString();

    bf.clear();
    bf.find(Xm);
    XmFactors = bf.toString();

    gmp_printf("$2^{%Zd}-1$ & %s & %Zd={$%s$} & $%s$ \\\\ \\hline \r\n",
               p.get_mpz_t(), type4k(p).c_str(), Xp.get_mpz_t(),
               XpFactors.c_str(), XmFactors.c_str());
  }

  printf("\\end{tabular}\r\n\\end{document}\r\n");
}

int main(int argc, char *argv[]) {
  argumentsHandler argHdl(argc, argv);
  int exponent, speed;
  int debugLevel;
  int action;
  vector<int> primeTable{
      2,  3,  5,  7,  11, 13, 17, 19, 23, 29,
      31, 37, 41, 43, 47, 53, 59, 61}; //,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199};

  argHdl.add(argument(0, (char *)"dz", (char *)"debug", (char *)"Debug level",
                      (char *)"N"));

  argHdl.add(argument(1, (char *)"a", (char *)"number",
                      (char *)"Number to be factorized", (char *)"N"));

  argHdl.add(argument(2, (char *)"b", (char *)"until",
                      (char *)"Process from 3 until N", (char *)"N"));

  argHdl.add(argument(3, (char *)"c", (char *)"primes",
                      (char *)"Process only prime table", (char *)"N"));

  argHdl.add(argument(4, (char *)"d", (char *)"aldo test",
                      (char *)"Process only prime table", (char *)"N"));

  argHdl.add(argument(5, (char *)"e", (char *)"aldo 2 test",
                      (char *)"Process only prime table", (char *)"N"));

  argHdl.add(argument(6, (char *)"f", (char *)"tirado 2 test",
                      (char *)"Process only prime table", (char *)"N"));

  argHdl.add(argument(7, (char *)"g", (char *)"F",
                      (char *)"Mersenne factorizer", (char *)"N"));

  argHdl.add(argument(8, (char *)"h", (char *)"H", (char *)"Tirado evaluation",
                      (char *)"N"));

  // segunda versión de la evalaución de Tirado

  argHdl.add(argument(9, (char *)"i", (char *)"i", (char *)"Tirado evaluation",
                      (char *)"N"));

  argHdl.add(argument(10, (char *)"j", (char *)"j",
                      (char *)"Tirado evaluation 3", (char *)"N"));

  argHdl.add(argument(11, (char *)"k", (char *)"K",
                      (char *)"Tirado evaluation 4", (char *)"N"));

  argHdl.add(argument(12, (char *)"l", (char *)"L",
                      (char *)"Tirado evaluation 5", (char *)"N"));

  /**
   * Buscar factores así: k * p + 1.. Si esto divide al mersenne entonces es
   * compuesto si se llega a la raiz cuadrada del mersenne no lo divide
   * */

  argHdl.add(argument(13, (char *)"m", (char *)"M",
                      (char *)"Experimento de Aldo, búsqueda por módulo",
                      (char *)"N"));

  /**
   * Buscar factores así: k * p + 1.. Si esto divide al mersenne entonces es
   * compuesto si se llega a la raiz cuadrada del mersenne no lo divide
   * SEGUNDA IMPLEMENTACION
   * */

  argHdl.add(argument(14, (char *)"n", (char *)"N",
                      (char *)"Experimento de Aldo, búsqueda por módulo",
                      (char *)"N"));

  /**
   * Implementa un bucle de búsqueda con exponentes primos
   * en números de mersenne que generan números compuestos
   * a efecto de estudiar las k...
   * */

  argHdl.add(argument(15, (char *)"o", (char *)"O",
                      (char *)"Experimento de Aldo, búsqueda por módulo",
                      (char *)"N"));

  /**
   * Descomposición de exponentes en la forma 2m+1
   * */

  argHdl.add(argument(16, (char *)"p", (char *)"O",
                      (char *)"Descomposición de exponentes en la forma 2m+1",
                      (char *)"N"));

  argHdl.add(argument(17, (char *)"q", (char *)"Q", (char *)"Obtener tiempo",
                      (char *)"N"));

  argHdl.add(
      argument(18, (char *)"r", (char *)"R", (char *)"Velocidad", (char *)"N"));

  argHdl.add(
      argument(19, (char *)"t", (char *)"T", (char *)"Velocidad", (char *)"N"));

  /* atomización*/
  argHdl.add(
      argument(20, (char *)"u", (char *)"U", (char *)"Velocidad", (char *)"N"));

  /* atomización doble modo */
  argHdl.add(
      argument(21, (char *)"v", (char *)"U", (char *)"Velocidad", (char *)"N"));

  /* Tomar todos los M no primos, y descomponer sus factores en la form 2pk+1
   */
  argHdl.add(
      argument(22, (char *)"w", (char *)"W", (char *)"Velocidad", (char *)"N"));

  /*** PRueba trivialll */
  argHdl.add(
      argument(23, (char *)"x", (char *)"W", (char *)"Exponente", (char *)"N"));

  /*** PRueba trivialll */
  argHdl.add(
      argument(24, (char *)"y", (char *)"W", (char *)"Exponente", (char *)"N"));

  argHdl.add(
      argument(25, (char *)"z", (char *)"W", (char *)"Exponente", (char *)"N"));

  while (action > -1) {
    action = argHdl.getAction();
    switch (action) {

    case 0:
      argHdl.pvalue(&debugLevel);
      break;

    case 1:
      argHdl.pvalue(&exponent);
      printf("2^%d-1:\r\n", exponent);
      tirado4a(exponent, debugLevel);
      cout << endl;
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
      for (int i = 0; i < primeTable.size(); i++) {
        printf("2^%d-1: \r\n", primeTable[i]);
        tirado4a(primeTable[i], debugLevel);
        cout << endl;
      }
      break;

      // Experimento de Aldo
    case 4:
      argHdl.pvalue(&exponent);
      tirado4b(exponent, debugLevel);
      break;

      // Experimetno de Aldo
    case 5:
      argHdl.pvalue(&exponent);
      tirado4c(exponent, debugLevel);

      break;

      // Division de los factorial por un factor p
    case 6:
      argHdl.pvalue(&exponent);
      tirado4e(exponent, debugLevel);

      break;
      // Cálculo de los argumentos de Tirado
    case 7:
      argHdl.pvalue(&exponent);
      tirado4f(exponent, debugLevel);

      break;
      // experimento de Tirado
    case 8:
      argHdl.pvalue(&exponent);
      tirado4h(exponent, debugLevel);

      break;

      // experimento de Tirado
    case 9:
      argHdl.pvalue(&exponent);
      tirado4i(exponent, debugLevel);
      break;
      // experimento de Tirado, con la variación de buscar argumentos primos
    case 10:
      argHdl.pvalue(&exponent);
      tirado4j(exponent, debugLevel);
      break;
    case 11:
      argHdl.pvalue(&exponent);
      tirado4k(exponent, debugLevel);
      break;
    case 12:
      argHdl.pvalue(&exponent);
      tirado4l(exponent, debugLevel);
      break;

    case 13:
      argHdl.pvalue(&exponent);
      tirado4m(exponent, debugLevel);
      break;

    case 14:
      argHdl.pvalue(&exponent);
      tirado4n(exponent, debugLevel);
      break;

    case 15:
      argHdl.pvalue(&exponent);
      tirado4o(exponent, debugLevel);
      break;

    case 16:
      argHdl.pvalue(&exponent);
      tirado4p(exponent, debugLevel);
      break;

    case 17:
      argHdl.pvalue(&exponent);
      // tirado4p(exponent, debugLevel);
      break;

    case 18:
      argHdl.pvalue(&speed);
      tirado4q(exponent, speed, debugLevel);
      break;

    case 19:
      argHdl.pvalue(&speed);
      tirado4t(exponent, debugLevel);
      break;

    case 20:
      argHdl.pvalue(&speed);
      tirado4u(exponent, debugLevel);
      break;

    case 21:
      argHdl.pvalue(&speed);
      tirado4v(exponent, debugLevel);
      break;

    case 22:
      argHdl.pvalue(&speed);
      tirado4w(exponent, debugLevel);
      break;

    case 23:
      argHdl.pvalue(&exponent);
      tirado4x(exponent, debugLevel);
      break;

    case 24:
      argHdl.pvalue(&exponent);
      tirado4y(exponent, debugLevel);
      break;

    case 25:
      argHdl.pvalue(&exponent);
      tirado4z(exponent, debugLevel);
      break;
    }
  }

  /** DEterminar que el número 2^(2^127-1)-1 termina el 7.
    // calculamos el mersenne
    mpz_class mersenne, mod;
    mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, 127);
    mersenne--;
    mpz_mod_ui(mod.get_mpz_t(), mersenne.get_mpz_t(), 4);
    gmp_printf("A=%Zd mod=%Zd", mersenne.get_mpz_t(), mod.get_mpz_t());
    */

  /*
   mpz_class mersenne, mod;
  for (int i=2; i<128; i++) {

      mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, 127);
      mersenne--;


  }
  */

  /*
  mpz_class mersenne, a, mod;
    mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, 127);
    mersenne--;
  */
}

// 2, 3, 5, 7, 11, 13, 17, 19, 23, 29. 31, 37, 41, 43, 47, 53, 59, 61, 67,