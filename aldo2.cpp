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
/*
bool is4kp1(mpz_class n) {
  int t = n.get_ui() % 4;
  if (t == 1 || t == 2) {
    return true;
  } else {
    return false;
  }
}
*/

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
  mutex locker;
  mpz_class a, b, f;
  a = min;

  locker.lock();
  gmp_printf("Thread min=%Zd begining\n", a.get_mpz_t());
  locker.unlock();

  while (reached == 0 && a < max) {
    //    b = (omega - a) / (p2 * a + 1);
    // f = p2 * a * b + a + b;

    b = (omega - a) % (p2 * a + 1);

    //   if (f == omega) {
    if (b == 0) {
      locker.lock();
      gmp_printf("Ks: %Zd, %Zd\a\n", a.get_mpz_t(), b.get_mpz_t());
      locker.unlock();
      break;
    }
    a++;
  }

  locker.lock();
  printf("Thread: %d finished.\n", reached);
  locker.unlock();
  reached++;
}

void primarityTest2(unsigned int p) {
  mpz_class p2, top, byThreads;
  mpz_class mersenne, omega, min, max;
  kdProcessBenchmark benchmark;
  vector<thread> threads;
  unsigned int nThreads = 5;
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
  cout.flush();
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
/*
int primarityTest(unsigned int p) {
  mpz_class mersenne; // mersenne number to be evaluate
  mpz_class t;        // multipurpose field
  mpz_class a, b;     // inner factors
  mpz_class omega;
  mpz_class fa, fb; // factors
  mpz_class root;   // root

  unsigned int mersenne_length;     // Digits of mersenne number
  unsigned int p_length;            // Digits of exponent
  unsigned int last_mersenne_digit; //
  unsigned int fa_length;
  unsigned int fb_length; // length of factor b
  unsigned int za, zb;    // correlative pointer to

  unsigned int border0 = 10000;
  unsigned int p2 = 2 * p; // Exponent * 2
  mpz_class sa[6], sb[6];
  unsigned int sc[6];

  // Calculate mersenne:
  mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, p);
  mersenne--;
  mpz_sqrt(root.get_mpz_t(), mersenne.get_mpz_t());

  // Calculate omega
  omega = (mersenne - 1) / (2 * p);

  // Calculate digits sizes:
  mersenne_length = mpz_sizeinbase(mersenne.get_mpz_t(), 10);
  p_length = log10(p) + 1;

  // Calculate last mersenne digits:
  mpz_mod_ui(t.get_mpz_t(), mersenne.get_mpz_t(), 10);
  last_mersenne_digit = t.get_ui();

  // Calculate a and b, trying
  a = 1;
  b = (omega - a) / (p2 * a + 1);

  // Factor a:
  fa = p2 + 1;

  // factor b
  fb = p2 * b + 1;

  // Last digits secuence
  sa[1] = (1 * p2 + 1) % 10;
  sa[2] = (2 * p2 + 1) % 10;
  sa[3] = (3 * p2 + 1) % 10;
  sa[4] = (4 * p2 + 1) % 10;
  sa[5] = (5 * p2 + 1) % 10;

  sb[1] = (b * p2 + 1) % 10;
  sb[2] = ((b - 1) * p2 + 1) % 10;
  sb[3] = ((b - 2) * p2 + 1) % 10;
  sb[4] = ((b - 3) * p2 + 1) % 10;
  sb[5] = ((b - 4) * p2 + 1) % 10;

  if (last_mersenne_digit == 1) {
    for (int i = 1; i <= 5; i++) {
      if ((sa[i] == 1 && sb[i] == 1) || (sa[i] == 3 && sb[i] == 7) ||
          (sa[i] == 7 && sb[i] == 3) || (sa[i] == 9 && sb[i] == 9)) {
        sc[i] = 1;
      } else {
        sc[i] = 0;
      }
    }
  }

  if (last_mersenne_digit == 7) {
    for (int i = 1; i <= 5; i++) {
      if ((sa[i] == 1 && sb[i] == 7) || (sa[i] == 7 && sb[i] == 1) ||
          (sa[i] == 3 && sb[i] == 9) || (sa[i] == 9 && sb[i] == 3)) {
        sc[i] = 1;
      } else {
        sc[i] = 0;
      }
    }
  }

  // Get sequencer
  za = 1;
  while (true) {
    if (sc[za] == 1) {
      if (mpz_divisible_p(mersenne.get_mpz_t(), fa.get_mpz_t()) == 0) {
        printf("Isn't prime.");
        return -1;
      }
    }
    za++;
    if (za == 6) {
      za = 1;
    }
    fa += p2;
    if (fa > root) {
      printf("Prime\n.");
      return 1;
    }
  }
}
*/

primeHolder::primeHolder(unsigned int theMersenneExponent, unsigned int n) {
  unsigned int p2 = 2 * theMersenneExponent;
  unsigned int t;

  this->mersenneExponent = theMersenneExponent;
  this->index = 1;
  this->prime = n;
  this->prime1 = n + 1;
  this->key = 1;

  t = p2 + 1;
  while (t % n != 0) {
    this->key++;
    t += p2;
  }
}

void primeHolder::reset(mpz_class kInitial) {
  mpz_class t;
  mpz_mod_ui(t.get_mpz_t(), kInitial.get_mpz_t(), this->prime);
  this->index = 1;
  for (int n = 1; n < t.get_ui(); n++) {
    this->next();
  }
}

bool primeHolder::next() {
  bool r = (this->index != this->key); // Return true if a coprime number
  this->index++;
  if (this->index == this->prime1) {
    this->index = 1;
  }
  return r;
}

primeSieve::primeSieve(unsigned int mersenneExponent, unsigned int upTo) {
  mpz_class t;
  t = 3;
  while (t.get_ui() <= upTo) {
    primeHolder ph(mersenneExponent, t.get_ui());
    this->holders.push_back(ph);
    mpz_nextprime(t.get_mpz_t(), t.get_mpz_t());
  }
  mpz_primorial_ui(this->primorial.get_mpz_t(), upTo);
  this->primorial /= 2;
}

void primeSieve::reset(mpz_class kInitial) {
  for (int i = 0; i < this->holders.size(); i++) {
    this->holders[i].reset(kInitial);
  }
}

bool primeSieve::next() {
  bool r = true;
  for (int i = 0; i < this->holders.size(); i++) {
    r &= this->holders[i].next();
  }
  return r;
}

float primeSieve::ratio() {
  this->reset();
  mpz_class i, j;

  for (i = 0; i < this->primorial; i++) {
    if (this->next())
      j++;
  }
  float r = 1 - (j.get_d() / this->primorial.get_d());
  return r;
}

int primarityTest_3(unsigned int p, unsigned int presieving, int debug) {

  mpz_class mersenne;
  mpz_class omega;
  mpz_class root;
  mpz_class limit; // k limit factor for number under squere root of mersenne

  mpz_class a, b, t, d;
  kdTimer kt;
  kdProcessBenchmark kpb;

  unsigned int i;
  // unsigned int j;
  // unsigned int k;
  unsigned int p2;

  p2 = 2 * p;

  // Get Mersenne
  mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, p);
  mersenne--;

  // Get omega:
  omega = (mersenne - 1) / (2 * p);

  // Get square root
  mpz_sqrt(root.get_mpz_t(), mersenne.get_mpz_t());

  if (debug > 0) {
    gmp_printf("Building sieve.\n");
  }

  primeSieve sieve(p, presieving);
  if (debug > 9) {
    gmp_printf("Ratio: %f. \n", sieve.ratio());
  }
  if (debug > 0) {
    gmp_printf("Starting process. \n");
  }

  kt.start();
  i = 0;
  t = p2 + 1;
  b = omega - 1;
  sieve.reset();
  kpb.start();
  while (true) {
    if (sieve.next()) {
      if (debug > 1) {
        if (!kpb.tick()) {
          gmp_printf("%Zd.\n", t.get_mpz_t());
        }
      }
      if (mpz_divisible_p(b.get_mpz_t(), t.get_mpz_t()) != 0) {
        a = (t - 1) / p2;
        gmp_printf("%Zd, %Zd\n ", a.get_mpz_t(), t.get_mpz_t());
        break;
      }
      if (t > root) {
        printf("Prime number.\n");
        break;
      }
    }
    b--;
    t += p2;
  }

  kpb.stop();
  printf("Time: %f.\n", kt.stop());
  return 1;
}

/*
void primarityTest_worker(int &threadn, int &reached, unsigned int p,
                          unsigned int presieve, mpz_class min,
                          mpz_class byThread, mpz_class mersenne,
                          mpz_class omega, mpz_class root) {
                            */

/*
void primarityTest_worker(int &threadn, int &reached, unsigned int presieve,
                          unsigned int p2, mpz_class w, mpz_class q) {
                            */

static mutex sync_printf_mutex;
int sync_printf(const char *format, ...) {
  va_list args;
  va_start(args, format);
  sync_printf_mutex.lock();
  gmp_vprintf(format, args);
  sync_printf_mutex.unlock();
  va_end(args);
  return 0;
}

void primarityTest_worker(int &threadn, int &reached, unsigned int p,
                          unsigned int presieve, mpz_class min, mpz_class max,
                          mpz_class omega, mpz_class root) {
  int ID = threadn++;

  // sync_printf("Init: %d. min=%Zd\n", ID, min.get_mpz_t());
  sync_printf("Init: %d.\n", ID);

  primeSieve sieve(p, presieve);
  mpz_class q, w, r, t, myByThread;
  unsigned int p2;

  p2 = 2 * p;
  w = p2 * min + 1;
  q = omega - min;
  sieve.reset(min);
  myByThread = max - min;

  while (true) {
    if (sieve.next()) {
      if (r > myByThread || reached > 0) {
        break;
      }
      if (mpz_divisible_p(q.get_mpz_t(), w.get_mpz_t()) != 0) {
        reached++;
        t = w / (p2);
        sync_printf("ID=%d, k=%Zd.\n", ID, t.get_mpz_t());
        break;
      }
    }
    q--;
    w += p2;
    r++;
    
  }

  sync_printf("Terminating %d.\n", ID);
}

int primarityTest(unsigned int p, unsigned int presieving, int nThreads,
                  unsigned int phases, int debug) {

  mpz_class mersenne;
  mpz_class omega;
  mpz_class root;
  mpz_class kByThread;
  mpz_class min, max, kMax;
  mpz_class a, b;
  int reached = 0;
  int threadn = 0;
  vector<thread> threads;
  kdTimer kt;
  int phase = 1;

  // Get Mersenne
  mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, p);
  mersenne--;

  // Get omega:
  omega = (mersenne - 1) / (2 * p);

  // Get square root
  mpz_sqrt(root.get_mpz_t(), mersenne.get_mpz_t());
  kMax = (root - 1) / (2 * p);

  kByThread = (kMax / (phases * nThreads)) + 1;

  min = 1;
  kt.start();

  for (phase = 0; phase < phases; phase++) {
    printf("Phase %d of %d.\n", phase, phases);
    threadn = 0;

    for (int i = 0; i < nThreads; i++) {
      max = min + kByThread;
      threads.emplace_back(thread(primarityTest_worker, ref(threadn),
                                  ref(reached), p, presieving, min, max, omega,
                                  root));
      min += kByThread;
    }

    for (thread &t : threads) {
      if (t.joinable()) {
        t.join();
      }
    }

    threads.clear();

    if (reached > 0) {
      break;
    }
    if (min > kMax) {
      break;
    }
  }

  if (reached == 0) {
    printf("Is prime!\n");
  }

  printf("Time: %f.\n", kt.stop());
  return 0;
}

int main(int argc, char *argv[]) {
  argumentsHandler argHdl(argc, argv);
  int exponent, speed;
  int debugLevel;
  int action;
  int maxPrime;
  int nThreads = 1;
  int64 p;
  int from = 0;
  int to = 0;
  int phases = 1;
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

  argHdl.add(argument(11, (char *)"m", (char *)"M", (char *)"Primarity test",
                      (char *)"N"));

  argHdl.add(argument(12, (char *)"h", (char *)"H", (char *)"Threads to use",
                      (char *)"N"));

  argHdl.add(
      argument(13, (char *)"s", (char *)"S", (char *)"Phases", (char *)"N"));

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
      // primarityTest(p);
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

    case 11:
      primarityTest(p, to, nThreads, phases, debugLevel);
      break;

    case 12:
      argHdl.pvalue(&nThreads);
      break;

    case 13:
      argHdl.pvalue(&phases);
      break;
    }
  }
}