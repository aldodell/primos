//#include "argumentsHandler.h"
//#include "bigGearsFactorizer.h"
#include "kdutils.h"
//#include <mpir.h>
//#include <gmp.h>
#include <gmpxx.h>
//#include <thread>

int main(int argc, char *argv[]) {

  int i = 1000000000;
  kdTimer kt;
  mpz_class a;
  mpz_ui_pow_ui(a.get_mpz_t(), 2, 64);
 
  a /= 20;
  a /= 1000000000;
  
  gmp_printf("bytes: %Zd \n\r", a.get_mpz_t());

  //  int64 a;
  a = 0;

  kt.start();
  while (true) {
    a++;
    if (a == i)
      break;
  }
  cout << kt.stop() << endl;

  exit(0);
}