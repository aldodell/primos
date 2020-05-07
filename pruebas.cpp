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

void test(int cycles) {
  kdProcessBenchmark benchmarker;
  benchmarker.cyclesForStep = cycles;

  /** Test fields */

  mpz_class m, n, k, p, p2;
  unsigned int md; // digitos de mersenne
  unsigned int fd; // digitos del factor

  p = 332192857;
  p2 = 2 * p;
  md = log10(2) * p.get_ui() + 1;

  mpz_ui_pow_ui(m.get_mpz_t(), 2, p.get_ui());
  m--;
  k = 1000;

  benchmarker.start();
  while (benchmarker.tick()) {
    /**       Coloque código de prueba aqui */
 
f = log10(p2.get_ui()) * k + 1;


    /** fin de Area de prueba */
  }
  benchmarker.stop();
}

int main(int argc, char *argv[]) {
  argumentsHandler argHdl(argc, argv);
  int debugLevel;
  int action;
  int cycles;

  argHdl.add(argument(0, (char *)"n", (char *)"N", (char *)"Cycles to test",
                      (char *)"N"));

  while (action > -1) {
    action = argHdl.getAction();
    switch (action) {
    case 0:
      argHdl.pvalue(&cycles);
      test(cycles);
      break;
    }
  }

  exit(0);
}