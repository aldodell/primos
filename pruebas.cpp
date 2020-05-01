//#include "argumentsHandler.h"
//#include "bigGearsFactorizer.h"
#include "kdutils.h"
//#include <mpir.h>
//#include <gmp.h>
#include <gmpxx.h>
//#include <thread>

/**
 * Área de pruebas de operaciones cíclicas
 * */

int main(int argc, char *argv[]) {
  kdProcessBenchmark benchmarker;
  benchmarker.cyclesForStep = 10000;

  /** Test fields */
  float f = 0;

  benchmarker.start();
  while (benchmarker.tick()) {
    /**       Coloque código de prueba aqui */
    f++;
    /** fin de Area de prueba */
  }
  benchmarker.stop();
  exit(0);
}