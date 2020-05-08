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
bool is4kp1(mpz_class n) {
  int t = n.get_ui() % 4;
  if (t == 1 || t == 2) {
    return true;
  } else {
    return false;
  }
}

/** Return 1 or 7, dependig wich digit M finish */
int lastDigit(mpz_class exponent) {
  mpz_class t = exponent / 2;
  if (mpz_tstbit(t.get_mpz_t(), 0) == 1) {
    return 7;
  } else {
    return 1;
  }
}

/* Retrieve Mersenne numbers information and trasnform it into CSV information
 */
void processA(int exp, bool putHeader) {

  mpz_class mersenne; // Mersenne base number
  mpz_class Xp;       // Exponent factor
  mpz_class Yp;
  mpz_class Xm;     // Mersenne number special factor;
  mpz_class k0;     // k in 4k+? on exponent
  mpz_class sk = 0; // K's sum.
  mpz_class pk = 1; // K's product.
  mpz_class zk = 0; // How many k are there?

  string XpFactors; // Exponent processed factors.
  string XmFactors; // Mersenne processed factors.
  string YpFactors;
  string MFactors;       // Mersenne processed factors.
  string XmDivXMFactors; // Mersenne processed factors.
  string k0Factors;      // Factors on k on 4k+?

  string ks;        // k from f=2*p*k+1
  mpz_class p;      // Exponent to evaluate
  mpz_class digits; // Digits of mersenne number

  vector<mpz_class> kss; // Vector of k's

  bigHalfGearFactorizer bf1, bf2;
  p = exp;

  if (putHeader) {
    // Put header:
    gmp_printf("p;"
               "Mersenne;"
               "p 4k+?;"
               "k in 4k+?;"
               "is prime?;"
               "digits;"
               "M last digit;"
               "Xp=(p-1)/2;"
               "Xp factors;"
               "Yp=(p+1)/2;"
               "Y factors;"
               "Xm=M-1/(6p);"
               "Xm Factors;"
               "How many factors?;"
               "M Factors;"
               "Factor's K;"
               "K's sum; "
               "K's product;"
               "Xm/Xp;");

    for (int i = 0; i < 10; i++) {
      gmp_printf("k%d;", i);
    }
    printf("\n");
  }

  // Get mersenne number:
  mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, p.get_ui());
  mersenne--;

  digits = (p.get_ui() * log10(2)) + 1;

  // Calculus
  Xp = (p - 1) / 2;
  Xm = (mersenne - 1) / (6 * p);
  bf1.clear();
  bf1.find(Xp);
  XpFactors = bf1.toString(true);

  bf2.clear();
  bf2.find(Xm);
  XmFactors = bf2.toString(true);

  XmDivXMFactors = bf2.divideBy(bf2.factors, bf1.factors, true);

  ks = " ";
  if (!isMersenneKnowPrimeExponent(p)) {
    bf1.clear();
    bf1.find(mersenne);
    MFactors = bf1.toString();
    std::sort(bf1.factors.begin(), bf1.factors.end());

    for (mpz_class k : bf1.factors) {
      k = (k - 1) / (2 * p);
      ks = ks + k.get_str() + ",";
      kss.push_back(k);
      sk += k;
      pk *= k;
    }
    zk = bf1.factors.size();
  }
  ks = ks.substr(0, ks.length() - 1);

  // k in 4k+?
  if (is4kp1(p)) {
    k0 = (p - 1) / 4;
  } else {
    k0 = (p - 3) / 4;
  }
  bf1.clear();
  bf1.find(k0);
  k0Factors = bf1.toString(true);
  if (k0Factors.length() == 0) {
    k0Factors = "1";
  }

  // Yp & Yp factors
  Yp = (p + 1) / 2;
  bf1.clear();
  bf1.find(Yp);
  std::sort(bf1.factors.begin(), bf1.factors.end());
  YpFactors = bf1.toString(true);

  // Put information on 'cout' with CSV format:
  gmp_printf("%Zd;", p.get_mpz_t());     // 2^p-1
  gmp_printf("2^%Zd-1;", p.get_mpz_t()); // 2^p-1
  gmp_printf("%s;", is4kp1(p) ? "4k+1" : "4k+3");
  gmp_printf("%s;", k0Factors.c_str());
  gmp_printf("%s;", yesOrNot(isMersenneKnowPrimeExponent(p)).c_str());
  gmp_printf("%Zd;", digits.get_mpz_t()); // Digits
  gmp_printf("%d;", lastDigit(p));        // Last Mersenne digit

  gmp_printf("%Zd;", Xp.get_mpz_t());    // Xp
  gmp_printf("'%s;", XpFactors.c_str()); // Factor of Xp
  gmp_printf("%Zd;", Yp.get_mpz_t());    // Yp
  gmp_printf("'%s;", YpFactors.c_str()); // Factor of Yp
  gmp_printf("'%Zd;", Xm.get_mpz_t());   // Xm
  gmp_printf("'%s;", XmFactors.c_str()); // Factor of Xm
  gmp_printf("'%Zd;", zk.get_mpz_t());   // How many factors?

  if (!isMersenneKnowPrimeExponent(p)) {
    gmp_printf("'%s;", MFactors.c_str()); // Factor of M
  } else {
    gmp_printf("'%Zd;", mersenne.get_mpz_t()); // Factor of M
  }
  gmp_printf("'%s';", ks.c_str());            // Ks of factors (if has)
  gmp_printf("'%Zd;", sk.get_mpz_t());        // K's sum.
  gmp_printf("'%Zd;", pk.get_mpz_t());        // K's product .
  gmp_printf("'%s;", XmDivXMFactors.c_str()); // K's product .

  // Put all k, cell by cell
  for (mpz_class kt : kss) {
    gmp_printf("\'%Zd;", kt.get_mpz_t()); // k.
  }

  gmp_printf("\n"); // End of line
}

void processB() {
  bigHalfGearFactorizer bf1;
  mpz_class p, Xp;

  printf("p;p 4k+?;Xp\n");

  for (int i = 0; i < 51; i++) {
    p = mersenneExponents[i];
    Xp = (p - 1) / 2;

    bf1.clear();
    bf1.find(Xp);

    gmp_printf("%Zd;", p.get_mpz_t());
    gmp_printf("%s;", is4kp1(p) ? "4k+1" : "4k+3");
    gmp_printf("%s", bf1.toString(true).c_str());
    printf("\n");
  }
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

/** Looking for first k if is a composite number */
/*
void lookFirstK(mpz_class p) {

  mpz_class mersenne; // Mersenne base number
  mpz_class Xp, XpFactors, p2, k, root, f, finish;
  bigHalfGearFactorizer bf;
  unsigned int t = 0;

  // Get mersenne number:
  mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, p.get_ui());
  mersenne--;
  Xp = (p - 1) / 2;

  // factorizing XP
  bf.clear();
  bf.find(Xp);

  // Detect if is a 4k+3:
  if (is4kp1(p)) {
    gmp_printf("Is a 4k+1\n");
  } else {
    gmp_printf("Is a 4k+3\n");
  }

  gmp_printf("Xp factors: %s \n", bf.toString().c_str());

  finish = p / 2;
  if (mpz_tstbit(finish.get_mpz_t(), 1) == 1) {
    gmp_printf("M finish with 7\n");
  } else {
    gmp_printf("M finish with 1\n");
  }


  if (mpz_divisible_ui_p(Xp.get_mpz_t(), 2) != 0) {
    gmp_printf("p has 2 factor.\n");
    return;
  }

  if (mpz_divisible_ui_p(Xp.get_mpz_t(), 3) != 0) {
    gmp_printf("p has 3 factor.\n");
    return;
  }
  */

/*
  p2 = 2 * p;
  f = p2 + 1;
  k = 1;

  printf("Calculating square root. ");
  cout.flush();
  mpz_sqrt(root.get_mpz_t(), mersenne.get_mpz_t());
  printf("Done!\n");

  while (mpz_divisible_p(mersenne.get_mpz_t(), f.get_mpz_t()) == 0) {
    if (f > root) {
      printf("Is prime.\n");
      return;
    }
    f += p2;
    k++;
    t++;
    if (t == 1000) {
      t = 0;
      gmp_printf("k=%Zd\n", k.get_mpz_t());
      cout.flush();
    }
  }

  gmp_printf("First k=%Zd, f=%Zd\n", k.get_mpz_t(), f.get_mpz_t());
}
*/

/** POR DESARROLLAR */
/*
void primarityTest(unsigned int exponent) {

  mpz_class k0, k1; // K en los factores de la forma 2pk+1
  mpz_class f0, f1; // Factores de 2^p-1
  mpz_class mersenne;
  unsigned int digitsOfmersenne;  // Dígitos del número de mersenne
  unsigned int lastDigitMersenne; //  Último dígito del Mersenne
  unsigned int lastDigitF0;       //  Último dígito del factor 0
  unsigned int lastDigitF1;       //  Último dígito del factor 0
  unsigned int p2;                // Exponente * 2

  // Calcular la cantidad de dígitos del número de Mersenne
  digitsOfmersenne = exponent * log10(2) + 1;

  // Determinar si el Mersenne termina en 7 o en 1
  lastDigitMersenne = exponent / 2;
  if (lastDigitMersenne && 1 == 1) {
    lastDigitMersenne = 7;
  } else {
    lastDigitMersenne = 1;
  }

  // Iniciamos con k0 = 1 para indicar que el primer "posible factor" es el más
  // bajo
  k0 = 1;

  // Algunos precálculos
  p2 = exponent * 2;

  int ex = 332192809;

  mpz_ui_pow_ui(f1.get_mpz_t(), 2, ex);
  f1 = f1 - 1;

  // Get mersenne number:
  // mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, p.get_ui());
  // mersenne--;

  f1 = (f1 - 1) / (2 * ex);
  gmp_printf("%10Zd", f1.get_mpz_t());

  // Evaluamos el dígito final del mersenne y decidimos cual k0 iniciará la
  // cuenta

  // while (true) {
  // f0 = p2 * k0 + 1;

  //}
}
*/

void primarityTest2_worker(int &reached, mpz_class omega, mpz_class p2,
                           mpz_class min, mpz_class max

) {

  mpz_class a, b, f;
  a = min;

  gmp_printf("Thread min=%Zd begining\n", a.get_mpz_t());

  while (reached == 0 && a < max) {
    b = (omega - a) / (p2 * a + 1);
    f = p2 * a * b + a + b;
    if (f == omega) {
      gmp_printf("Ks: %Zd, %Zd\a\n", a.get_mpz_t(), b.get_mpz_t());
      break;
    }
    a++;
  }

  printf("Thread: %d finished.\n", reached);
  reached++;
}

void primarityTest2(unsigned int p) {
  mpz_class p2, top, byThreads;
  mpz_class mersenne, omega, min, max;
  kdProcessBenchmark benchmark;
  vector<thread> threads;
  unsigned int nThreads = 50;
  int reached = 0;

  p2 = 2 * p;

  mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, p);
  mersenne--;
  omega = (mersenne - 1) / p2;
  mpz_sqrt(top.get_mpz_t(), mersenne.get_mpz_t());
  top = top / (p2 + 1);
  byThreads = top / nThreads;

  for (int i = 0; i < nThreads; i++) {
    min = (i * byThreads) + 1;
    max = min + byThreads - 1;
    threads.emplace_back(
        thread(primarityTest2_worker, ref(reached), omega, p2, min, max));
  }

  while (reached < nThreads) {
  }
  printf("Reached: %d\n", reached);
}

void analysis(unsigned int p, unsigned int limit) {
  setlocale(LC_ALL, "da-DK");
  mpz_class mersenne, Xp, Xm, p2, k, first, fa, fb, ma, mb, dmab;
  mpz_class diva, divb, root, rootLimit;

  int i;

  // Get mersenne
  mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, p);
  mersenne--;

  Xm = (mersenne - 1) / 2;
  p2 = 2 * p;
  first = (mersenne - 1) / p2;

  mpz_root(root.get_mpz_t(), mersenne.get_mpz_t(), 2);
  rootLimit = root / p2;

  gmp_printf("M: %'Zd\n", mersenne.get_mpz_t());
  gmp_printf("Limit: %'Zd\n", first.get_mpz_t());
  gmp_printf("Root: %'Zd\n", root.get_mpz_t());
  gmp_printf("Root limit: %'Zd\n", rootLimit.get_mpz_t());

  if (limit == 0)
    limit = first.get_ui();

  printf("%15s %15s %15s %15s %15s %15s %15s \n", "k", "2pk", "(M-1)/(2pk)",
         "2pk+1", "M/(2pk+1)", "(M-1)%(2pk)", "M%(2pk+1)" /*, "Dif"*/);
  for (k = 1; k <= limit; k++) {

    fa = p2 * k;
    fb = fa + 1;
    ma = (mersenne - 1) % fa;
    mb = (mersenne) % fb;
    dmab = ma - mb;
    diva = (mersenne - 1) / fa;
    divb = (mersenne) / fb;

    gmp_printf("%15Zd %15Zd %15Zd %15Zd %15Zd %15Zd %15Zd\n",
               k.get_mpz_t(), fa.get_mpz_t(), diva.get_mpz_t(), fb.get_mpz_t(),
               divb.get_mpz_t(), ma.get_mpz_t(), mb.get_mpz_t()/*,
               dmab.get_mpz_t()*/);
  }
}

/** Calcula mersenne, lo divide por 2pk+1 y calcula el módulo */
void analysis2(unsigned int to, unsigned int from) {
  mpz_class mersenne, p, f, k, mod;
  bigHalfGearFactorizer bf;
  vector<mpz_class> factors;

  p = 3;
  printf("p;m;Xp;p:4k+?;k:4k+?\n");
  for (int i = 0; i < to; i++) {
    // Get mersenne
    mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, p.get_ui());
    mersenne--;
    f = (2 * p) + 1;
    mpz_mod(mod.get_mpz_t(), mersenne.get_mpz_t(), f.get_mpz_t());
    // if (mod == from) {
    if (p % 10 == 7) {
      gmp_printf("%'Zd;", p.get_mpz_t());   // p
      gmp_printf("%'Zd;", mod.get_mpz_t()); // m
      bf.clear();
      bf.find((p - 1) / 2);

      for (mpz_class f : bf.factors) {
        if (find(factors.begin(), factors.end(), f) == factors.end()) {
          factors.push_back(f);
        }
      }

      printf("%s;", bf.toString(true).c_str());
      if (is4kp1(p)) {
        printf("4k+1;");
        k = (p - 1) / 4;
      } else {
        printf("4k+3;");
        k = (p - 3) / 4;
      }
      bf.clear();
      bf.find(k);
      gmp_printf("%s;", bf.toString(true).c_str()); // k
      printf("\n");
    }
    //}
    mpz_nextprime(p.get_mpz_t(), p.get_mpz_t());
  }

  printf("\n");
  p = 3;
  auto max = *max_element(factors.begin(), factors.end());
  for (int i = 0; i <= max.get_ui(); i++) {
    if (find(factors.begin(), factors.end(), p) == factors.end()) {
      gmp_printf("%Zd;\n", p.get_mpz_t());
    }
    mpz_nextprime(p.get_mpz_t(), p.get_mpz_t());
  }
  printf("\n");
}

/** Intent to get a fast primarity test for Mersenne's numbers*/

void primarityTest(unsigned int p) {
  mpz_class mersenne;           // mersenne number to be evaluate
  mpz_class T;                  // multipurpose field
  unsigned int mersenne_digits; // Digits of mersenne number
  unsigned int p_digits;        // Digits of exponent
  unsigned int last_mersenne_digits;
  unsigned int a, b; // Inner factors

  // Calculate mersenne:
  mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, p);
  mersenne--;

  // Calculate digits sizes:
  mersenne_digits = (p * log10(2)) + 1;
  p_digits = log10(p) + 1;

  // Calculate last mersenne digits:
  mpz_mod_ui(T.get_mpz_t(), mersenne.get_mpz_t(), pow(10, p_digits));
  last_mersenne_digits = T.get_ui();

  while(true) {



  }





}

int main(int argc, char *argv[]) {
  argumentsHandler argHdl(argc, argv);
  int exponent, speed;
  int debugLevel;
  int action;
  int maxPrime;
  int64 p;
  int from = 0;
  int to = 0;
  mpz_class exp;

  argHdl.add(argument(0, (char *)"d", (char *)"debug", (char *)"Debug level",
                      (char *)"N"));

  argHdl.add(argument(1, (char *)"p", (char *)"exponent",
                      (char *)"Set exponent on 2^p-1", (char *)"N"));

  argHdl.add(argument(2, (char *)"f", (char *)"from",
                      (char *)"Define p to begin", (char *)"N"));

  argHdl.add(argument(3, (char *)"t", (char *)"to", (char *)"Define p to end",
                      (char *)"N"));

  argHdl.add(argument(4, (char *)"r", (char *)"range",
                      (char *)"Init process with 2^p-1 with p0=f & pn=t",
                      (char *)"N"));

  argHdl.add(
      argument(5, (char *)"k", (char *)"test", (char *)"FREE", (char *)"N"));

  argHdl.add(argument(6, (char *)"j", (char *)"J",
                      (char *)"Test for a particular p", (char *)"N"));

  argHdl.add(argument(7, (char *)"a", (char *)"A",
                      (char *)"Analysis particular p", (char *)"N"));
  argHdl.add(
      argument(8, (char *)"b", (char *)"B", (char *)"Analysis 2", (char *)"N"));

  argHdl.add(argument(9, (char *)"c", (char *)"c",
                      (char *)"Analysis only Prime Mersenne numbers",
                      (char *)"N"));

  argHdl.add(argument(10, (char *)"l", (char *)"L",
                      (char *)"Composite mersenne test", (char *)"N"));

  while (action > -1) {
    action = argHdl.getAction();

    switch (action) {

    case 0:
      argHdl.pvalue(&debugLevel);
      break;

    case 1:
      argHdl.pvalue(&p);
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

    case 5:
      break;

    case 6:
      primarityTest(p);
      break;

    case 7:
      analysis(p, to);
      break;

    case 8:
      analysis2(to, from);
      break;

    case 9:
      processB();
      break;

    case 10:
      primarityTest2(p);
      break;
    }
  }
}