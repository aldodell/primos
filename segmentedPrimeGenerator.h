#ifndef SEGMENTED_PRIME_GENERATOR_H
#define SEGMENTED_PRIME_GENERATOR_H
#include "argumentsHandler.h"
#include "kdutils.h"
#include <algorithm>
#include <mutex>
#include <thread>

#define BLOCKS_BY_FILE 10000000
//#define NUMBERS_TO_UPDATE_FILE 1000000

struct primePart {
  int64 begin;
  int64 end;
};

class segmentedPrimeGenerator {

public:
  //

  int debugLevel = 0;
  string filePrefix = "bd/prime_";
  // Move the index and return prime number
  int64 move(int step);
  // Move to next:
  int64 next();
  // Move to next:
  int64 nextTo(int64 number);
  // Move previusly
  int64 prev();
  void reset();
  void clearBuffer();

  void generate(int64 max, int64 partsCount);

  /**
   * Determine coordinates of each number
   * Recieve a prime number
   * Return, the file index
   * a block (byte) into the file
   * a offset (bit mask) into de byte
   */
  void inline calculatePosition(int64 number, int &fileIndex, int64 &block,
                                int &offset);
  int64 inline calculateNumber(int64 position, int &fileIndex, int64 &block,
                               int &offset);

  void inline setNotPrime(vector<int64> &buffer);
  void save(int fileIndex);
  void load(int fileIndex);
  string getFileName(int fileIndex);

  // internal index
  int64 index = 0;
  int fileIndex = -1;
  int64 maximum = 0;

  // Buffer of bitmask
  vector<unsigned char> buffer;
  // Number buffer
  vector<int64> buffer2;

  // Mutex for buffer2
  mutex mutexBuffer;
};

void generatorAux(primePart *part, segmentedPrimeGenerator *spg);
void updateFile(segmentedPrimeGenerator *spg);

struct normalized {
  int64 value;
  int index;
};

normalized normalizer(int64 number);

#endif