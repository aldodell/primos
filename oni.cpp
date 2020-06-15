/**
 * Some functions using ONIs Algebra (By Eleazar Tirado)
 * */

#include "oni.h"

mpz_class oni_sum(mpz_class a, mpz_class b) {
  mpz_class i; // counter
  mpz_class s; // sum
  for (i = a; i <= b; i += 2) {
    s += i;
  }
  return s;
}

void oni_primarity(mpz_class z) {
  kdProcessBenchmark benckmark;
  mpz_class a, b, q, r, s;
  a = 3;
  b = 2 * z - 1;
  q = z * z;
  s = (q + 1) / 2;

  benckmark.cyclesForStep = 10000000;
  printf("Calculating first ONI serie.\n");
  benckmark.start();
  r = (((a + b) / 2) * (((b - a) / 2) + 1)); //
  benckmark.stop();

  printf("Calculating primarity.\n");
  benckmark.start();

  while (true) {
    benckmark.tick();
    gmp_printf("%Zd\t%Zd\t%Zd\n", a.get_mpz_t(), b.get_mpz_t(), r.get_mpz_t());
    if (r == q) {
      gmp_printf("%Zd isn't prime. a=%Zd, b=%Zd.\n", z.get_mpz_t(),
                 a.get_mpz_t(), b.get_mpz_t());
      break;
    }

    while (r > q) {
      r -= a;
      a += 2;
    }

    while (r < q) {
      b += 2;
      r += b;
    }

    if (a > s) {
      gmp_printf("%Zd is prime. a=%Zd, b=%Zd.\n", z.get_mpz_t(), a.get_mpz_t(),
                 b.get_mpz_t());
      break;
    }
  }
  benckmark.stop();
}

void oni_test1(unsigned int a, unsigned int b) {

  unsigned int p;
  unsigned int i;
  unsigned int j;
  bigHalfGearFactorizer bf;
  mpz_class q = 2;

  mpz_class lt, m, n, f, g;
  string s[]{"no primo", "probablemente primo", "primo"};

  gmp_printf("p;lt;prime\n");
  for (i = a; i < b; i++) {
    p = mersenneExponents[i];
    // mpz_nextprime(q.get_mpz_t(), q.get_mpz_t());
    mpz_ui_pow_ui(m.get_mpz_t(), 2, p);
    m--;
    lt = 2 * m - 1;
    j = mpz_probab_prime_p(lt.get_mpz_t(), 15);
    bf.clear();
    bf.find(lt);
    gmp_printf("2^%d-1;2M-1 *%s*;%s.", p, s[j].c_str(),
               bf.toString(true).c_str());

    sort(bf.factors.begin(), bf.factors.end());
    for (int i = 0; i < bf.factors.size(); i++) {
      f = bf.factors[i];
      mpz_mod_ui(n.get_mpz_t(), f.get_mpz_t(), 22);
      g = f / 22;
      gmp_printf("\n\t%Zd=2*11*%Zd+%Zd ", f.get_mpz_t(), g.get_mpz_t(),
                 n.get_mpz_t());
    }
    printf("\n");
  }
}

/** Este test busca los números de Mersenne con p terminados en 7 y prueba
 * si 2M-1 es divisibles por 11
 * */
void oni_test2(int a, int b) {
  int i;
  int p;
  mpz_class m;
  for (i = 0; i < 51; i++) {
    p = mersenneExponents[i];

    if (p % 10 == a) {
      mpz_ui_pow_ui(m.get_mpz_t(), 2, p);
      m--;
      m = 2 * m - 1;

      if (mpz_divisible_ui_p(m.get_mpz_t(), b) != 0) {
        printf("2*(2^%d-1)-1 es divisible por %d.\n", p, b);
      } else {
        printf("2*(2^%d-1)-1 NO es divisible por %d.\n", p, b);
      }
    }
  }
}

int main(int argc, char *argv[]) {
  argumentsHandler argHdl(argc, argv);

  int debugLevel;
  int action;
  mpz_class a, b;

  argHdl.add(argument(0, (char *)"z", (char *)"debug", (char *)"Debug level",
                      (char *)"N"));

  argHdl.add(argument(1, (char *)"a", (char *)"A", (char *)"a parameter",
                      (char *)"N"));

  argHdl.add(argument(2, (char *)"b", (char *)"B", (char *)"b parameter",
                      (char *)"N"));

  argHdl.add(argument(3, (char *)"s", (char *)"sum",
                      (char *)"ONI sum from a to b", (char *)"N"));

  argHdl.add(argument(4, (char *)"p", (char *)"primarity",
                      (char *)"Primarity test of 'a' param.", (char *)"N"));

  argHdl.add(argument(5, (char *)"e", (char *)"experiment1",
                      (char *)"Take last term o ONI on Mersenne N",
                      (char *)"N"));

  argHdl.add(argument(6, (char *)"f", (char *)"experiment2",
                      (char *)"P ends at 7 are 2M-1 divisible by 11",
                      (char *)"N"));

  while (action > -1) {
    action = argHdl.getAction();

    switch (action) {

    case 0:
      argHdl.pvalue(&debugLevel);
      break;

    case 1:
      a = argHdl.value;
      break;

    case 2:
      b = argHdl.value;
      break;

    case 3:
      gmp_printf("%Zd\n", oni_sum(a, b).get_mpz_t());
      break;

    case 4:
      oni_primarity(a);
      break;

    case 5:
      oni_test1(a.get_ui(), b.get_ui());
      break;

    case 6:
      oni_test2(a.get_ui(), b.get_ui());
      break;
    }
  }

  exit(0);
}