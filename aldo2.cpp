/**
 * This application search some properties on Mersenne numbers
 * */
#include "aldo2.h"

bool isMersenneKnowPrimeExponent(mpz_class p) {
  int n = p.get_ui();
  bool r = find(mersenneExponents.begin(), mersenneExponents.end(), n) !=
           mersenneExponents.end();
  return r;
}

/** Return if a number is a 4k+1 */
bool is4kp1(mpz_class n) { return ((n - 1) % 4 == 0); }

/* Retrieve Mersenne numbers information and trasnform it into CSV information
 */
void processA(int maxPrime) {

  mpz_class mersenne; // Mersenne base number
  mpz_class Xp;       // Exponent factor
  mpz_class Xm;       // Mersenne number special factor;
  string XpFactors;   // Exponent processed factors.
  string XmFactors;   // Mersenne processed factors.
  mpz_class p;        // Exponent to evaluate

  bigHalfGearFactorizer bf;
  p = 1;

  // Put header:
  gmp_printf("\"Mersenne\"; \"p 4k+?\"; \"is prime?\"; \"Xp=(p-1)/2\"; \"Xp "
             "factors\"; "
             "\"Xm=M-1/(6p)\"; "
             "\"Xm Factors\";\r\n");

  while (p < maxPrime) {

    mpz_nextprime(p.get_mpz_t(), p.get_mpz_t());

    // Get mersenne number:
    mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, p.get_ui());
    mersenne--;

    // Calculus
    Xp = (p - 1) / 2;
    Xm = (mersenne - 1) / (6 * p);
    bf.clear();
    bf.find(Xp);
    XpFactors = bf.toString();
    bf.clear();
    bf.find(Xm);
    XmFactors = bf.toString();

    // Put information on 'cout' with CSV format:
    gmp_printf("\"2^%Zd-1\"; ", p.get_mpz_t()); // 2^p-1
    gmp_printf("\"%s\"; ", is4kp1(p) ? "4k+1" : "4k+3");
    gmp_printf("\"%s\"; ", yesOrNot(isMersenneKnowPrimeExponent(p))
                               .c_str());      // Is a know mersenne prime?
    gmp_printf("\"%Zd\"; ", Xp.get_mpz_t());   // Xp
    gmp_printf("\"%s\"; ", XpFactors.c_str()); // Factor of Xp
    gmp_printf("\"%Zd\"; ", Xm.get_mpz_t());   // Xm
    gmp_printf("\"%s\"; ", XmFactors.c_str()); // Factor of Xm

    gmp_printf("\r\n"); // End of line
  }
}
int main(int argc, char *argv[]) {
  argumentsHandler argHdl(argc, argv);
  int exponent, speed;
  int debugLevel;
  int action;
  int maxPrime;

  argHdl.add(argument(0, (char *)"d", (char *)"debug", (char *)"Debug level",
                      (char *)"N"));

  argHdl.add(argument(1, (char *)"a", (char *)"",
                      (char *)"Init process, a=Max prime to evaluate.",
                      (char *)"N"));

  while (action > -1) {
    action = argHdl.getAction();
    switch (action) {

    case 0:
      argHdl.pvalue(&debugLevel);
      break;

    case 1:

      argHdl.pvalue(&maxPrime);
      processA(maxPrime);
      break;
    }
  }
}