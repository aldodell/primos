#include "mersenne.h"

/**
 * Little program used for generate Mersenne's numbers
 * */

string mersenne(int64 p) {
  mpz_class m;
  mpz_ui_pow_ui(m.get_mpz_t(), 2, p);
  mpz_sub_ui(m.get_mpz_t(), m.get_mpz_t(), 1);
  return m.get_str();
}

/**
 * Worker function. This is executed by some threads.
 * Try to find a factors. Brute force primarity test
 * */
void *worker(void *args) {

  DataFinder *dataFinder = (DataFinder *)args;
  mpz_class k, f, p2;

  p2 = 2 * dataFinder->p;
  k = dataFinder->fromK;

  while (true) {

    // Test if there are other thread wich found a factor.
    if (!dataFinder->keepAlive) {
      break;
    }

    // Factor to test
    f = (p2 * k) + 1;
    if (mpz_divisible_p(dataFinder->m.get_mpz_t(), f.get_mpz_t()) != 0) {
      dataFinder->found = true;
      dataFinder->keepAlive = false;
      dataFinder->foundK = &k;
      break;
    }

    k++;
    if (k == dataFinder->toK) {
      dataFinder->found = false;
      break;
    }
  }
}

/** INCOMPLETE: THIS APPROACH MAY BE NOT WORKS PROPERLY
 *
 *
 * Handle threads to try to factorize
 * */
void toFind(unsigned int exponent, int howManyThreads) {

  bool keepAlive = true;
  bool found = false;
  vector<pthread_t> threads;
  mpz_class M, kMax, root;

  // Get Mersenne
  mpz_ui_pow_ui(M.get_mpz_t(), 2, exponent);
  M--;

  // Get root;
  mpz_sqrt(root.get_mpz_t(), M.get_mpz_t());

  // get kMax:
  kMax = (root - 1) / exponent;

  for (int i = 0; i < howManyThreads; i++) {
    DataFinder df();
    // df->m = M;
  }
}

#ifndef MERSENNE_LIB
int main(int argc, char *argv[]) {

  // argument handler:
  argumentsHandler argHdl(argc, argv);
  int action = 0;
  int debugLevel = 0;
  int64 n;
  int threadsQuantity = 1;

  argHdl.add(argument(0, (char *)"d", (char *)"debug", (char *)"Debug level",
                      (char *)"N"));

  argHdl.add(argument(1, (char *)"p", (char *)"number", (char *)"p in (2^p-1)",
                      (char *)"N"));

  argHdl.add(argument(2, (char *)"s", (char *)"sqr", (char *)"Square root",
                      (char *)"N"));

  argHdl.add(argument(3, (char *)"t", (char *)"T", (char *)"How many threads",
                      (char *)"N"));

  argHdl.add(argument(4, (char *)"f", (char *)"F",
                      (char *)"Find factors. Use with -p:", (char *)""));

  while (action > -1) {
    action = argHdl.getAction();
    switch (action) {

    case 0:
      argHdl.pvalue(&debugLevel);
      break;

    case 1:
      argHdl.pvalue(&n);
      cout << mersenne(n) << endl;
      break;

    case 2:
      argHdl.pvalue(&n);
      mpz_class r, m;
      m = mersenne(n);

      mpz_sqrt(r.get_mpz_t(), m.get_mpz_t());
      cout << r << endl;
      break;

    case 3:
      argHdl.pvalue(&threadsQuantity);
      break;

    case 4:
      toFind(n, threadsQuantity);
      break;
    }

    exit(0);
  }
#endif