#include "primos.h"

/**
 *      Main
 */

int main(int argc, char *argv[]) {
  const int64 initLoadNumber = 1 << 20;
  // input number to be factorized

  int64 maxNumber = 0;

  // file name with prime numbers
  char primeFilename[32];

  // CLI user action code
  int action = 0;

  // Actions flags
  bool loadTableFlag = false;
  bool proccessFlag = false;
  bool showFlag = false;
  bool listFlag = false;
  bool openfactorizerCLI = false;
  bool showLast = false;
  bool findErrorFlag = false;

  // Debug level
  int debugLevel;

  // Time between user interface update
  int seconds;

  // Multipurpose tags
  int64 begin, end;

  // Prime number generator
  primeGenerator pg;

  // Factorizer
  factorizer factorizer(&pg);

  // argument handler:
  argumentsHandler argHdl(argc, argv);

  argHdl.add(argument(0, (char *)"f", (char *)"file",
                      (char *)"Prime number file", (char *)"filename"));
  argHdl.add(argument(1, (char *)"n", (char *)"number",
                      (char *)"Max prime number", (char *)"N"));
  argHdl.add(argument(2, (char *)"s", (char *)"show", (char *)"Show statics",
                      (char *)""));
  argHdl.add(argument(3, (char *)"i", (char *)"list",
                      (char *)"Show primes number list", (char *)""));
  argHdl.add(argument(4, (char *)"p", (char *)"process",
                      (char *)"Calculate prime numbers", (char *)""));
  argHdl.add(argument(5, (char *)"l", (char *)"load", (char *)"Load table",
                      (char *)""));
  argHdl.add(argument(6, (char *)"t", (char *)"time",
                      (char *)"Time to update UI(seconds)", (char *)"s"));
  argHdl.add(argument(7, (char *)"d", (char *)"debug", (char *)"Debug level",
                      (char *)"n"));
  argHdl.add(argument(8, (char *)"x", (char *)"factorize",
                      (char *)"Open factorizer CLI", (char *)""));
  argHdl.add(argument(9, (char *)"z", (char *)"last",
                      (char *)"Show last found prime number", (char *)""));
  argHdl.add(argument(10, (char *)"b", (char *)"begin",
                      (char *)"Margin for some process", (char *)""));
  argHdl.add(argument(11, (char *)"e", (char *)"end",
                      (char *)"Margin for some process", (char *)""));
  argHdl.add(argument(12, (char *)"r", (char *)"error", (char *)"Find errors",
                      (char *)""));

  while (action > -1) {
    action = argHdl.getAction();
    switch (action) {
    case 0:
      argHdl.pvalue(primeFilename, sizeof(primeFilename));
      cout << "File: " << primeFilename << endl;

      break;

    case 1:

      argHdl.pvalue(&maxNumber);

      cout << "Max number: " << maxNumber << endl;
      break;

    case 2:
      showFlag = true;
      break;

    case 3:
      listFlag = true;
      break;

    case 4:
      proccessFlag = true;
      break;

    case 5:
      loadTableFlag = true;
      break;

    case 6:

      argHdl.pvalue(&seconds);

      cout << "Time to update UI: " << seconds << " seconds" << endl;
      break;

    case 7:

      argHdl.pvalue(&debugLevel);
      cout << "Debug level: " << debugLevel << endl;
      // pt.debugLevel = debugLevel;
      break;

    case 8:
      openfactorizerCLI = true;
      break;

    case 9:
      showLast = true;
      break;

    case 10:

      argHdl.pvalue(&begin);
      cout << "Begin: " << begin << endl;

      break;

    case 11:

      argHdl.pvalue(&end);
      cout << "End: " << end << endl;

      break;

    case 12:
      findErrorFlag = true;
      break;

    default:
      break;
    }
  }

  if (loadTableFlag) {
    pg.load(primeFilename);
  }

  if (showFlag) {
  }
  if (listFlag) {
    pg.list(begin, end);
  }

  if (proccessFlag) {
    pg.generate(maxNumber);
    pg.save(primeFilename);
  }

  if (showLast) {
    cout << "Last number on file " << primeFilename << ": ";
    cout << p1000(pg.last()) << endl;
  }

  if (findErrorFlag) {
    int64 k = 1;
    pg.reset();
    while (true) {
      k = pg.next();
      if (k == 0)
        break;

      if (k > end)
        break;

      if (k >= begin) {

        if (k % 2 == 0) {
          cout << "Error % 2 " << k << endl;
        }

        if (k % 3 == 0) {
          cout << "Error % 3 " << k << endl;
          break;
        }

        if (k % 5 == 0) {
          cout << "Error % 5 " << k << endl;
          break;
        }

        if (k % 7 == 0) {
          cout << "Error % 7 " << k << endl;
          break;
        }
      }
    }
  }

  if (openfactorizerCLI) {
    int64 n;

    while (true) {
      cout << "Write a number to factorize or 0 for exit:" << endl;
      cin >> n;
      if (n == 0)
        break;
      factorizer.debugLevel = debugLevel;
      factorizer.reset();
      factorizer.find(n);
      cout << factorizer.toString() << endl;
    }
  }

  return EXIT_SUCCESS;
}
