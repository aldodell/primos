#include "primelib.h"

bool is4k1(mpz_class p, int debugLevel) {
  mpz_class t = p - 1;
  bool r = false;
  if (mpz_divisible_ui_p(t.get_mpz_t(), 4) != 0) {
    r = true;
  }
  if (debugLevel > 0) {
    if (r) {
      gmp_printf("%Zd is 4k+1 form.\n", p.get_mpz_t());
    } else {
      gmp_printf("%Zd is 4k+3 form.\n", p.get_mpz_t());
    }
  }
  return r;
}

char *firstk(mpz_class p) {
  mpz_class m, o, q, w, p2, t;
  mpz_ui_pow_ui(m.get_mpz_t(), 2, p.get_ui());
  unsigned limit = 100;
  m--;
  o = (m - 1) / (2 * p);
  p2 = 2 * p;

  q = o - 1;
  w = p2 + 1;

  while (mpz_divisible_p(q.get_mpz_t(), w.get_mpz_t()) != 0 && limit-- > 0) {
    q--;
    w += p2;
  }
  t = q / w;
  return (char *)t.get_str().c_str();
}

/** Send to CSV some properties of prime numbers from a to b */
void test0(mpz_class a, mpz_class b, int debugLevel) {
  mpz_class n, m;
  bigHalfGearFactorizer gf;

  printf("p;(p-1)/2;4k+?;p factors;k0\n");
  mpz_nextprime(n.get_mpz_t(), a.get_mpz_t());

  while (n < b) {
    m = (n - 1) / 2;
    gf.clear();
    gf.find(m);

    gmp_printf("%Zd;%Zd;%s;%s;%s\n", n.get_mpz_t(), m.get_mpz_t(),
               is4k1(n, 0) ? "4k+1" : "4k+3", gf.toString().c_str(), firstk(n));

    mpz_nextprime(n.get_mpz_t(), n.get_mpz_t());
  }
}

#ifndef PRIMELIB_LIB

int main(int argc, char *argv[]) {

  // argument handler:
  argumentsHandler argHdl(argc, argv);
  bigHalfGearFactorizer gf;

  int action = 0;
  int debugLevel = 0;

  mpz_class n, m, a, b;
  kdTimer kt;

  argHdl.add(argument(1, (char *)"d", (char *)"debug", (char *)"Debug level",
                      (char *)"N"));

  argHdl.add(argument(1, (char *)"4k1", (char *)"number",
                      (char *)"Number is 4k1 form", (char *)"N"));

  argHdl.add(argument(2, (char *)"4k3", (char *)"number",
                      (char *)"Number is 4k3 form", (char *)"N"));

  argHdl.add(argument(3, (char *)"x", (char *)"number",
                      (char *)"Properties of a number", (char *)"N"));

  argHdl.add(argument(4, (char *)"y", (char *)"number",
                      (char *)"Properties of a set of numbers (from a to b)",
                      (char *)"N"));

  argHdl.add(argument(5, (char *)"a", (char *)"number", (char *)"Parameter a",
                      (char *)"N"));

  argHdl.add(argument(6, (char *)"b", (char *)"number", (char *)"Parameter b",
                      (char *)"N"));

  while (action > -1) {
    action = argHdl.getAction();
    switch (action) {
    case 0:
      argHdl.pvalue(&debugLevel);
      break;

    case 1:
      n = argHdl.value;
      return is4k1(n, debugLevel);
      break;

    case 2:
      n = argHdl.value;
      return !is4k1(n, debugLevel);
      break;

    case 3:
      n = argHdl.value;
      m = (n - 1) / 2;
      gf.clear();
      gf.find(m);
      gmp_printf("Properties of: %Zd.\n", n.get_mpz_t());

      if (is4k1(n)) {
        printf("p is 4k+1.\n");
      } else {
        printf("p is 4k+3.\n");
      }

      printf("Factors of (p-1)/2 = %s.\n ", gf.toString().c_str());
      break;

    case 4:
      test0(a, b, 0);
      break;

    case 5:
      a = argHdl.value;
      break;

    case 6:
      b = argHdl.value;
      break;
    }
  }
}

#endif