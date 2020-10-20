#include "factors32.h"
int main(int argc, char *argv[]) {
  unsigned int n = atoi(argv[1]);

  vector<unsigned int> factors;

  factorizer(n, factors);

  string s;
  for (unsigned int q : factors) {
    s = is4k3(q) ? "4k+3" : "4k+1";
    printf("%d : %s\n", q, s.c_str());
  }
}
