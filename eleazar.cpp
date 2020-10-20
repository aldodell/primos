/**
 * 04 de Octubre de 2020.
 * Hoy muere en la ciudad de Caracas Don Eleazar Tirado.
 * Dios lo reciba en su casa.
 * */
#include "eleazar.h"

void eleazar(int exponent) {
  mpz_class mersenne, q, q1, q2, p, k, root, t;

  p = exponent;

  // Calculate mersenne 2^p-1
  mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, exponent);
  mersenne--;

  // Get square root
  mpz_sqrt(root.get_mpz_t(), mersenne.get_mpz_t());

  // Discard factors: 2pk+1
  k = 2 * p;
  q = k + 1;
  q1 = q - 1;
  q2 = q + 1;

  while (true) {

    if (q1 > root) {
      printf("Is prime!\n");
      return;
    }

    if ((mpz_divisible_ui_p(q1.get_mpz_t(), 8) != 0) ||
        (mpz_divisible_ui_p(q2.get_mpz_t(), 8) != 0)) {
      q = q1 + 1;
      if (mpz_divisible_p(mersenne.get_mpz_t(), q.get_mpz_t()) != 0) {
        gmp_printf("Factor found: %Zd\n", q.get_mpz_t());
        return;
      }
    }

    q1 += k;
    q2 += k;
  }
}

int main(int argc, char *argv[]) {
  argumentsHandler argHdl(argc, argv);

  int action;
  int debugLevel = 0;
  int max = 4;
  int n = 0;

  argHdl.add(argument(0, (char *)"n", (char *)"number",
                      (char *)"Number to be factorized", (char *)"N"));
  argHdl.add(argument(1, (char *)"d", (char *)"debug", (char *)"Debug level",
                      (char *)"N"));

  while (action > -1) {
    action = argHdl.getAction();
    switch (action) {
    case 0:
      argHdl.pvalue(&n);
      eleazar(n);
      // n = argHdl.value;
      break;
    case 1:
      argHdl.pvalue(&debugLevel);
      break;
    }
  }
}
