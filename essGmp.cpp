#include "essGmp.h"

/**
 * Eratosthenes Segmented Sieve
 * */

/** Sieve for segment */
void essGmp::generateMain(mpz_class min, mpz_class max, bool save) {
  kdTimer kt;
  kt.start();
  mpz_class mpzSegmentSize;
  mpzSegmentSize = (max - min) / 20;

  // Size in bytes of bits for store primes
  int segmentSize = mpzSegmentSize.get_ui();

  // Data array. Are "char" but means "bytes"
  // vector<unsigned char> buffer(segmentSize, 0);
  vector<unsigned char> buffer(segmentSize, 0);

  // data variables:
  mpz_class a, b, p, q, q2, m2;

  // Indices:
  int i, j, offset, flag, m, block;

  /* Separator array for 1,3,7,9
  Store deltas to increment 'a' and 'b' to numbers of the secuence:
  3,7,9,11,13,17,19,21....
  */
  // int s[] = {2, 4, 2, 2};
  int s[] = {2, 4, 2, 2};

  // Get close to the next odd significant number
  a = 3;
  i = 1;

  // Main process
  while (true) {

    // Normalizer begin block

    // Obtenemos el último dígito y lo acercamos a algún número de la serie:
    b = min / a;
    m2 = b % 10;
    m = m2.get_ui();
    // int index;

    switch (m) {
    case 0:
      if (b == 0) {
        b = 3;
        j = 1;
      } else {
        b = b - m + 1;
        j = 0;
      }
      break;
    case 1:
      b = b - m + 1;
      j = 0;
      if (b == 1) {
        b = 3;
        j = 1;
      }
      break;
    case 2:
      b = b - m + 3;
      j = 1;
      break;
    case 3:
      b = b - m + 3;
      j = 1;
      break;
    case 4:
      b = b - m + 7;
      j = 2;
      break;
    case 5:
      b = b - m + 7;
      j = 2;
      break;
    case 6:
      b = b - m + 7;
      j = 2;
      break;
    case 7:
      b = b - m + 7;
      j = 2;
      break;
    case 8:
      b = b - m + 9;
      j = 3;
      break;
    case 9:
      if (b == 9) {
        b = 11;
        j = 0;
      } else {
        b = b - m + 9;
        j = 3;
      }
      break;
    }

    // Normalizer end block

    while (true) {
      p = a * b;
      if (p > max)
        break;

      if (p > min) {

        // Mark bit block begin
        q = p - min;
        block = q.get_ui() / 20;
        q = q - (20 * block);
        offset = q.get_ui();

        switch (offset) {
        case 1:
          flag = 0;
          break;

        case 3:
          flag = 1;
          break;

        case 7:
          flag = 2;
          break;

        case 9:
          flag = 3;
          break;

        case 11:
          flag = 4;
          break;

        case 13:
          flag = 5;
          break;

        case 17:
          flag = 6;
          break;

        case 19:
          flag = 7;
          break;
        }

        buffer[block] |= 1 << flag;
        // Mark bit block end
      }

      // Increment b to te next OSN (Odd significant number)
      b += s[j];
      j++;
      if (j == 4)
        j = 0;
    }
    a += s[i];
    i++;
    if (i == 4)
      i = 0;
    if ((a * a) > max)
      break;
  }

  if (save) {
    // Build filename
    string filename = "bd/primes_" + min.get_str() + "_" + max.get_str();

    // Build file:
    ofstream ofs(filename, ios_base::binary);

    // Save file
    ofs.write((char *)&buffer[0], buffer.size());
    ofs.flush();
    ofs.close();
  }

  cout << "Segment " << min << " - " << max << " finished on " << kt.stop()
       << " seconds." << endl;
}

inline int essGmp::getFlag(int64 block, int offset) {
  int flag = 0;
  switch (offset) {
  case 1:
    flag = 0;
    break;

  case 3:
    flag = 1;
    break;

  case 7:
    flag = 2;
    break;

  case 9:
    flag = 3;
    break;

  case 11:
    flag = 4;
    break;

  case 13:
    flag = 5;
    break;

  case 17:
    flag = 6;
    break;

  case 19:
    flag = 7;
    break;
  }

  return flag;
}

/** Return:
 * 1 if number is prime
 * 0 if number isn't prime
 * -1 if number is out of range
 * */
int essGmp::isPrime(vector<unsigned char> &buffer, mpz_class number,
                    mpz_class min) {
  // Trivial answers:
  for (int i : this->trivialPrimerTable) {
    if (i == number.get_ui())
      return 1;
  }

  // less than 2 -> exit
  if (number < 2)
    return 0;

  // If number is even return false:
  if ((number & 1) == 0) {
    return 0;
  }

  // if number is 5 multiple return false:
  if ((number % 10) == 5) {
    return 0;
  }

  mpz_class t1, t2, t3;

  /*
    // Get byte to evaluate
    int64 block = ((number - min) / 20);

    // If number is out of range return -1
    if (block > buffer.size())
      return -1;

    // Get offset
    int offset = (number - min) - (20 * block);
  */

  // Get byte to evaluate
  t1 = number - min;
  t2 = t1 / 20;
  int block = t2.get_ui();

  // If number is out of range return -1
  if (block > buffer.size())
    return -1;

  // Get offset
  t3 = t1 - (20 * block);
  int offset = t3.get_ui();

  // Get byte to evaluate at offset
  int q = buffer.at(block);

  // Get bit position (flag)
  int flag = this->getFlag(block, offset);
  if (!(q & (1 << flag)))
    return 1;

  // Isn't prime, return 0.
  return 0;
}
/**
 * Build data base file with prime numbers table
 * from 2 to 10^exponent
 * */
void essGmp::generate(int exponent) {

  vector<std::thread> ts;
  mpz_class min, max, maxTotal, files, segment;
  mpz_ui_pow_ui(maxTotal.get_mpz_t(), 10, exponent);

  files = (maxTotal / 20) / this->filesize;

  if (files == 0)
    files = 1;

  segment = maxTotal / files;

  for (int i = 0; i < files; i++) {
    min = i * segment;
    max = min + segment;
    ts.push_back(std::thread(essGmp::generateMain, min, max, true));
    cout << "Segment:" << min << "-" << max << " starting." << endl;
    // ts.emplace_back(&generateMain, min, max, true);
  }

  for (std::thread &t : ts) {
    t.join();
  }
}

int main(int argc, char *argv[]) {

  // argument handler:
  argumentsHandler argHdl(argc, argv);
  essGmp es;
  int action = 0;
  int command = 0;
  int debugLevel = 0;
  mpz_class a, b;
  int exponent = 3;

  argHdl.add(argument(0, (char *)"a", (char *)"number", (char *)"Minimun",
                      (char *)"N"));

  argHdl.add(argument(1, (char *)"b", (char *)"number", (char *)"Maximum",
                      (char *)"N"));

  argHdl.add(argument(2, (char *)"d", (char *)"debug", (char *)"Debug level",
                      (char *)"N"));

  argHdl.add(argument(3, (char *)"g", (char *)"generate",
                      (char *)"Generate and save on files", (char *)"N"));

  argHdl.add(argument(4, (char *)"e", (char *)"exponet",
                      (char *)"Generate and save on files. 10^e", (char *)"N"));

  while (action > -1) {
    action = argHdl.getAction();
    switch (action) {
    case 0:
      // argHdl.pvalue();
      a = argHdl.value;
      break;

    case 1:
      // argHdl.pvalue();
      b = argHdl.value;
      break;

    case 2:
      argHdl.pvalue(&debugLevel);
      break;

    case 3:
      command = 1;
      break;

    case 4:
      argHdl.pvalue(&exponent);
      break;
    }
  }

  // gf.debugLevel = debugLevel;
  kdTimer kt;
  kt.start();

  if (command == 1) {
    es.generate(exponent);
  }

  // cout << gf.toString() << " (" << kt.stop() << ")" << endl;

  return 0;

  // essGmp e1;
  // kdTimer kt;

  // vector<unsigned char> buffer;
  // kt.start();

  // mpz_class x, y, b, j;

  // mpz_ui_pow_ui(x.get_mpz_t(), 2, 64);
  // y = x + 200;

  // e1.generate(buffer, x, y);
  // cout << kt.stop() << endl;

  // for (j = x; j < y; j++) {
  //   if (e1.isPrime(buffer, j, x) == 1) {
  //     cout << " " << j << endl;
  //   }
  // }
}