#ifndef KDUTILS_H

#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <sstream>

#define CALL_MEMBER_FN(object, ptrToMember) ((object).*(ptrToMember))

using namespace std;

/** Type used for calculate big primes of b bytes (2^64) */
typedef unsigned long long int int64;

using namespace std;

/** Prototypes */
char *concat(char *a, char *b);
char *concatchar(char *c1, char *c2, char *c3 = nullptr, char *c4 = nullptr,
                 char *c5 = nullptr, char *c6 = nullptr);
char *stringToChar(string &value);
char *p1000(unsigned long long value);
void kdebug(char *message, int levelRequired, int debugLevel);
bool file_exists(const std::string &name);

class kdTimer {
public:
  void start();
  double stop();
  double snapshoot();

private:
  size_t tIni, tSnap, tEnd;
};

class kdProcessSpin {
public:
  kdProcessSpin();
  void reset();
  void show();
  unsigned int cyclesForStep = 1000000;
  vector<char *> marks;

private:
  unsigned int cycles = 0;
  int index = 0;
};

std::string string_join(const std::vector<std::string>& elements, const char* const separator);



#define KDUTILS_H
#endif
