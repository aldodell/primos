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
void processA(int exp, bool putHeader) {

  mpz_class mersenne; // Mersenne base number
  mpz_class Xp;       // Exponent factor
  mpz_class Xm;       // Mersenne number special factor;
  mpz_class tmp;
  string XpFactors; // Exponent processed factors.
  string XmFactors; // Mersenne processed factors.
  string MFactors;  // Mersenne processed factors.
  string ks;        // k from f=2*p*k+1
  mpz_class p;      // Exponent to evaluate

  bigHalfGearFactorizer bf;
  p = exp;

  if (putHeader) {
    // Put header:
    gmp_printf("\"Mersenne\"; \"p 4k+?\"; \"is prime?\"; \"Xp=(p-1)/2\"; \"Xp "
               "factors\"; "
               "\"Xm=M-1/(6p)\"; "
               "\"Xm Factors\"; \"M Factors\"; \"Factor's K\"; \r\n");
  }

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

  ks = " ";
  if (!isMersenneKnowPrimeExponent(p)) {
    bf.clear();
    bf.find(mersenne);
    MFactors = bf.toString();

    for (mpz_class k : bf.factors) {
      k = (k - 1) / (2 * p);
      ks = ks + k.get_str() + ",";
    }
  }
  ks = ks.substr(0, ks.length() - 1);

  // Put information on 'cout' with CSV format:
  gmp_printf("\"2^%Zd-1\"; ", p.get_mpz_t()); // 2^p-1
  gmp_printf("\"%s\"; ", is4kp1(p) ? "4k+1" : "4k+3");
  gmp_printf("\"%s\"; ", yesOrNot(isMersenneKnowPrimeExponent(p))
                             .c_str());      // Is a know mersenne prime?
  gmp_printf("\"%Zd\"; ", Xp.get_mpz_t());   // Xp
  gmp_printf("\"%s\"; ", XpFactors.c_str()); // Factor of Xp
  gmp_printf("\"%Zd\"; ", Xm.get_mpz_t());   // Xm
  gmp_printf("\"%s\"; ", XmFactors.c_str()); // Factor of Xm
  if (!isMersenneKnowPrimeExponent(p)) {
    gmp_printf("\"%s\"; ", MFactors.c_str()); // Factor of M
  } else {
    gmp_printf("\"%Zd\"; ", mersenne.get_mpz_t()); // Factor of M
  }
  gmp_printf("\"%s\"; ", ks.c_str()); // Ks of factors (if has)

  gmp_printf("\r\n"); // End of line
}

/** Loop for evaluate some p on 2^p-1 */
void processRange(int from, int to) {
  mpz_class p = from;
  bool sendHeader = true;
  mpz_nextprime(p.get_mpz_t(), p.get_mpz_t());
  while (p < to) {
    processA(p.get_ui(), sendHeader);
    sendHeader = false;
    mpz_nextprime(p.get_mpz_t(), p.get_mpz_t());
  }
}

int main(int argc, char *argv[]) {
  argumentsHandler argHdl(argc, argv);
  int exponent, speed;
  int debugLevel;
  int action;
  int maxPrime;
  int p;
  int from, to;

  argHdl.add(argument(0, (char *)"d", (char *)"debug", (char *)"Debug level",
                      (char *)"N"));

  argHdl.add(argument(1, (char *)"p", (char *)"exponent",
                      (char *)"Init process with 2^p-1", (char *)"N"));

  argHdl.add(argument(2, (char *)"f", (char *)"from",
                      (char *)"Define p to begin", (char *)"N"));

  argHdl.add(argument(3, (char *)"t", (char *)"to", (char *)"Define p to end",
                      (char *)"N"));

  argHdl.add(argument(4, (char *)"r", (char *)"range",
                      (char *)"Init process with 2^p-1 with p0=f & pn=t",
                      (char *)"N"));

  while (action > -1) {
    action = argHdl.getAction();
    switch (action) {

    case 0:
      argHdl.pvalue(&debugLevel);
      break;

    case 1:
      argHdl.pvalue(&p);
      processA(p, true);
      break;

    case 2:
      argHdl.pvalue(&from);
      break;

    case 3:
      argHdl.pvalue(&to);
      break;

    case 4:
      processRange(from, to);
      break;
    }
  }
}