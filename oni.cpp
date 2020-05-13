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
  mpz_class a, b, q, r, s, d, t;
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
    } else if (r > q) {

      // 1+sqrt(b^2+2*b-4*i+1)

      if (r - q > 4) {
        mpz_pow_ui(t.get_mpz_t(), b.get_mpz_t(), 2);
        t = t + (2 * b) - (4 * q) + 1;
        mpz_sqrt(t.get_mpz_t(), t.get_mpz_t());
        t++;
        if (mpz_tstbit(t.get_mpz_t(), 0) == 0) {
          t--;
        }
        d = ((t + a) / 2) * (((t - a) / 2) + 1);
        r -= d;
        a = t + 2;
      } else {
        r -= a;
        a += 2;
      }
    } else if (r < q) {

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

//  gmp_printf("%Zd isn't prime. a=%Zd, b=%Zd\n", z.get_mpz_t(),
// a.get_mpz_t(), b.get_mpz_t());

// gmp_printf("%Zd is prime\n", z.get_mpz_t());

void oni_test1() {

  unsigned int p;
  unsigned int i;
  unsigned int j;

  mpz_class lt, m;
  string s[]{"no primo", "probablemente primo", "primo"};

  // gmp_printf("p;lt;prime\n");
  for (i = 0; i < 30; i++) {
    p = mersenneExponents[i];
    mpz_ui_pow_ui(m.get_mpz_t(), 2, p);
    m--;
    lt = 2 * m - 1;
    j = mpz_probab_prime_p(lt.get_mpz_t(), 15);
    // gmp_printf("*2^%d-1*=%Zd.\n*2M-1*=%Zd.\n*%s.*\n\n", p, m.get_mpz_t(),
    // lt.get_mpz_t(),
    //          s[j].c_str());

    gmp_printf("*2^%d-1*. 2M-1 *%s*.\n", p, s[j].c_str());
    //cin.ignore();
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
      oni_test1();
      break;
    }
  }

  exit(0);
}