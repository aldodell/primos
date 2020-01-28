#include "tirado2.h"

/**
 * Show "addends" of 2^(n-1) like odd sumatory
 * */

/*
void tirado2(int n, primeTester &pt) {

  unsigned int i, j;
  int k;
  int twinPrimes;
  int twinPrimes2;

  mpz_class p, p1, p2;
  mpz_class min;
  mpz_class center;
  mpz_class lastTwin;

  int centerExp;
  int addendsExp;
  int addendsN;
  int totalTwinPrimes = 0;
  int elementsByLine = 8;
  int maxCharsByLine = 80;
  bool condition1 = false; // first mode has even addens
  bool condition2 = false; // there is almost one mode with 2^p*5^r addens

  string mark, ps("0");
  mpz_class lastPrime(0);
  bool isPrime;
  int modes = (n - 1) / 2;

  printf("\n\r<hr>\n\r");
  printf("<h1>Computing 2<sup>%d-1</sup>. Modes: %d.</h1></br><ul>", n, modes);


  for (i = modes; i > 1; i--) {

    centerExp = n - i - 1;
    mpz_ui_pow_ui(center.get_mpz_t(), 2, centerExp);
    addendsExp = i;
    addendsN = pow(2, addendsExp);
    min = center - addendsN + 1;
    twinPrimes = 0; // twin primes counter
    lastPrime = 0;

    gmp_printf("<li>Mode %d.Center=2<sup>%d</sup>=%Zd. "
               "Addends=2<sup>%d</sup>=%d.</li>",
               i, centerExp, center.get_mpz_t(), addendsExp, addendsN);

    k = maxCharsByLine;
    printf("<table style=\"width:100%%\"><tr>");

    for (j = 0; j < addendsN; j++) {
      p = min + (2 * j);
      ps = p.get_str();
      if (ps == "1" || pt.test(ps)) {
        if (lastPrime == (p - 2) && lastPrime != lastTwin) {
          lastTwin = p;
          twinPrimes++;
          totalTwinPrimes++;
          k = k - gmp_printf("<th>%Zd,%Zd</th>", lastPrime.get_mpz_t(),
                             p.get_mpz_t());
          if (k < 0) {
            k = maxCharsByLine;
            printf("</tr><tr>");
          }
        }
        lastPrime = p;
      }
    }

    printf("</tr></table><br><k><b>Total twin primes in mode "
           "%d=%d.</k></b></br></br>",
           i, twinPrimes);

    if (i == modes) {
      // is even?
      condition1 = (twinPrimes & 1) == 0;
    }
    if (condition1 && i < modes) {
      twinPrimes2 = twinPrimes;
      // Check if there are 2 factors
      while (twinPrimes2 % 2 == 0) {
        twinPrimes2 /= 2;
        if (twinPrimes2 == 1)
          condition2 = true;
      }

      while (twinPrimes2 % 5 == 0) {
        twinPrimes2 /= 5;
        if (twinPrimes2 == 1)
          condition2 = true;
      }
    }
  }

  printf("</ul></br>");
  printf("<h2>Total twin primes in (2<sup>%d-1</sup>) = %d.</h2>", n,
         totalTwinPrimes);

  if (condition1 && condition2) {
    printf("<h2>2<sup>%d-1</sup> pass test", n);
  }

  printf("</br>");
}
 */

void tirado2(int n, primeTester &pt) {

  int m = n - 1;
  int modes = m / 2;
  int mode;
  int expCenter;
  int expAddends;
  unsigned int addends;
  mpz_class center;
  mpz_class min;
  mpz_class p, p2;
  mpz_class lastPrime;
  mpz_class lastTwin;
  string ps;
  bool flag1, flag2;
  unsigned int twins = 0;

  printf("<h1>Computing 2<sup>%d-1</sup></h1>", n);

  for (mode = modes; mode > 1; mode--) {

    expCenter = m - mode;
    expAddends = mode;

    // Get center:
    mpz_ui_pow_ui(center.get_mpz_t(), 2, expCenter);
    
    // Get addends
    addends = powl(2, expAddends);

    // Get minimun
    min = center - addends + 1;

    gmp_printf("<h2>Mode %d. Center=2<sup>%d</sup>=%Zd. Addends=2^%d=%d.</h2>",
               mode, expCenter, center.get_mpz_t(), expAddends, addends);

    for (int i = 0; i < addends; i++) {
      p = min + (2 * i);
      p2 = p - 2;
      ps = p.get_str();

      if ((ps == "1" ||
           ((pt.test(ps)) && (p2 == lastPrime) && (p2 != lastTwin)))) {
        twins++;
        lastTwin = p;
        printf("%s \n\r", ps.c_str());
      }
      lastPrime = p;
    }
    if (mode == modes) {
      if ((twins & 1) == 0) {
        flag1 = true;
        printf("<k><b>Mode %d. Has even addends</b></k>", mode);
      }
    } else {
      if (flag1) {
      }
    }
  }
}

int main(int argc, char *argv[]) {
  argumentsHandler argHdl(argc, argv);

  int action;
  int command;
  int min = 0, max = 0;
  int debugLevel;

  argHdl.add(argument(0, (char *)"a", (char *)"number",
                      (char *)"Minimun exponent", (char *)"N"));

  argHdl.add(argument(1, (char *)"b", (char *)"number",
                      (char *)"Maximum exponent", (char *)"N"));

  argHdl.add(argument(2, (char *)"d", (char *)"debug", (char *)"Debug level",
                      (char *)"N"));

  while (action > -1) {
    action = argHdl.getAction();
    switch (action) {
    case 0:
      argHdl.pvalue(&min);
      break;

    case 1:
      argHdl.pvalue(&max);
      break;

    case 2:
      argHdl.pvalue(&debugLevel);
      break;
    }
  }

  if (max > 0) {

    // Initial text for HTML:
    const char *head = R"html(
<html>
<head>
<style>
table {
  font-family: arial, sans-serif;
  //border-collapse: collapse;
  width: 100%;
}

td, th {
  border: 1px solid #dddddd;
  text-align: right;
  //padding: 8px;
}

tr:nth-child(even) {
  //background-color: #dddddd;
}
</style>
</head>
<body>
)html";

    cout << head;
    primeTester pt(0);
    pt.reset();
    int i = pt.next(min);
    while (true) {
      tirado2(i, pt);
      i = pt.next(i);
      if (i > max)
        break;
    }

    cout << "</html>";
  }

  exit(0);
}