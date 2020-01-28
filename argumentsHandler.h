#ifndef ARGUMENTS_HANDLERS_H
#define ARGUMENTS_HANDLERS_H
#include "kdutils.h"
#define MAX_ARGS 32

/** Type used for calculate big primes of b bytes (2^64) */
typedef unsigned long long int int64;

using namespace std;

/**
 * Prototypes
 **/

class argument {
public:
  int id;
  char *shortName;
  char *longName;
  char *value;
  char *description;
  char *expected;

  argument(int id, char *shortName, char *longName, char *description,
           char *expected);
};

/**
 * Arguments handler
 * Usage:
 * (1) Instatiate an object:
 *              argumentHandler argHdl(argc, argv);
 * (2) Load commands:
 *              argHdl.add(argument(int id,chr* short,chr* long ,chr*
 * description,chr* expected)) argHdl.add(argument(1,"s","show","Show data",""))
 * Parameters:
 * id: Command id
 * short: Short name for command.
 * long: Long name for command.
 * desc: Description.
 * expected: Value wich must be declared after separator. Usually ":"
 *
 *
 * */
class argumentsHandler {
private:
  int argc;
  char *argv[MAX_ARGS];
  int index;

public:
  std::vector<argument> arguments;

  char *separator;
  char *shortPrefix;
  char *longPrefix;

  argumentsHandler(int argc, char *argv[]);
  ~argumentsHandler();
  void add(argument arg);
  std::string value;

  int getAction();
  void showHelp();
  void pvalue(char *destination, int length);
  void pvalue(int *destination);
  void pvalue(double *destination);
  void pvalue(long *destination);
  void pvalue(int64 *destination);
};

#endif
