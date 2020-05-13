#include "argumentsHandler.h"
//#include "bigGearsFactorizer.h"
#include "kdutils.h"
//#include <mpir.h>
//#include <gmp.h>
#include <gmpxx.h>
//#include <thread>

/**
 * Área de pruebas de operaciones cíclicas
 * */
void myTest(int p, int cycles);

void myTest(int p, int cycles) {

  kdProcessBenchmark benchmarker;
  benchmarker.cyclesForStep = cycles;

  /** Test fields */

  mpz_class m, a, b, z0, z1, omega;
  int n;
  unsigned int p2;
  p2 = 2 * p;

  mpz_ui_pow_ui(m.get_mpz_t(), 2, p);
  m--;
  a = 1;

  omega = (m - 1) / (p2);

  benchmarker.start();
  //  z0 = omega - 1;
  // z1 = p2 + 1;
  z1 = 1000000000;
  while (benchmarker.tick()) {

    mpz_mod(z0.get_mpz_t(), m.get_mpz_t(), z1.get_mpz_t());

    /*
       n = mpz_divisible_p(z0.get_mpz_t(), z1.get_mpz_t());
       if (n != 0) {
         gmp_printf("f0=%Zd\n", z1.get_mpz_t());
         break;
       }
       z0--;
       z1 += p2;
       */
    /** fin de Area de prueba */
  }
  benchmarker.stop();
  gmp_printf("f0=%Zd\n", z0.get_mpz_t());
}

int main(int argc, char *argv[]) {
  argumentsHandler argHdl(argc, argv);
  int debugLevel;
  int action;
  int cycles = 0;
  int p = 1;

  argHdl.add(argument(0, (char *)"n", (char *)"N", (char *)"Cycles to test",
                      (char *)"N"));

  argHdl.add(argument(1, (char *)"p", (char *)"P", (char *)"Cycles to test",
                      (char *)"N"));

  while (action > -1) {
    action = argHdl.getAction();
    switch (action) {
    case 0:
      argHdl.pvalue(&cycles);
      break;
    case 1:
      argHdl.pvalue(&p);
    }
  }

  myTest(p, cycles);
  exit(0);
}