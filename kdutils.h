#ifndef KDUTILS_H

#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <locale>
#include <sstream>
#include <string>
#include <vector>

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

class kdProcessBenchmark {
public:
  unsigned int cyclesForStep = 1000000;
  unsigned int cycles = 0;
  bool tick();
  void start();
  void stop();

private:
  size_t tIni, tSnap, tEnd;
};

class kdPocketBit {
public:
  kdPocketBit(size_t size, bool initial = false);
  void set(int64 position, bool status);
  bool get(int64 position);
  vector<unsigned char> data;
  void reset();
  void write(bool status);
  bool read();
  void pass();

private:
  int64 index;
  unsigned char offest;
  unsigned char byte;
};

std::string string_join(const std::vector<std::string> &elements,
                        const char *const separator);

template <typename T> bool ifExists(vector<T> &vect, T &elem);

string yesOrNot(bool booleanValue);

#define KDUTILS_H
#endif
