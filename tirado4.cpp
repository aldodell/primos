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
    pivot--;
  }

  /*
    while (mpz_tstbit(pivot.get_mpz_t(), 0) == 0) {
      pivot /= 2;
    }
    */

  // Imprimimos:
  gmp_printf("2^%d - 1 = %Zd\r\n", exponent, mersenne.get_mpz_t());
  gmp_printf("Square root = %Zd\r\n", root.get_mpz_t());

  while (true) {
    if (mpz_probab_prime_p(pivot.get_mpz_t(), 50) > 0) {
      argument = (pivot - 1) / 2;
      mpz_mod_ui(mod.get_mpz_t(), argument.get_mpz_t(), exponent);
      if (mod == 0) {
        gmp_printf("\r\npivot=%Zd\r\n", pivot.get_mpz_t());
        gmp_printf("argument(2m+1): %Zd\r\n", argument.get_mpz_t());
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

int main(int argc, char *argv[]) {
  argumentsHandler argHdl(argc, argv);
  int exponent;
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
    }
  }
}

// 2, 3, 5, 7, 11, 13, 17, 19, 23, 29. 31, 37, 41, 43, 47, 53, 59, 61, 67,