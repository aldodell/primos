#include "aldo.h"

void aldo() {

  primeTester pt(0);
  bigGearsFactorizer bgf();

  unsigned int a = 0;
  mpz_class m;
  string s;

  while (true) {
    a = pt.next(a);
    s = mersenne(a);
    mpz_init_set_str(m.get_mpz_t(), s.c_str(), 10);
    bgf.find(
  }
}