#include "insumo1.h"
int main(int argc, char const *argv[]) {

  vector<unsigned int> factors;
  unsigned int t;

  for (unsigned int p : MPE) {
    factors.clear();
    t = (p - 1) / 2;

    if (t > 1) {
      factorizer(t, factors);
      printf("=== %d(%s) ===\n", p, is4k1(p) ? "4k+1" : "4k+3");
      show4kXform(factors);
      printf("\n");
    }
  }

  return 0;
}
