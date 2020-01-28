#include "ess.h"

/**
 * Eratosthenes Segmented Sieve
 * */

/**
 * Function with take a number and return a number wich are close
 * to array [1,3,7,9]...
 * */
normalized normalizer(int64 value) {
  // Obtenemos el último dígito y lo acercamos a algún número de la serie:
  int64 m = value % 10;
  int index;

  switch (m) {
  case 0:
    if (value == 0) {
      value = 3;
      index = 1;
    } else {
      value = value - m + 1;
      index = 0;
    }
    break;
  case 1:
    value = value - m + 1;
    index = 0;
    if (value == 1) {
      value = 3;
      index = 1;
    }
    break;
  case 2:
    value = value - m + 3;
    index = 1;
    break;
  case 3:
    value = value - m + 3;
    index = 1;
    break;
  case 4:
    value = value - m + 7;
    index = 2;
    break;
  case 5:
    value = value - m + 7;
    index = 2;
    break;
  case 6:
    value = value - m + 7;
    index = 2;
    break;
  case 7:
    value = value - m + 7;
    index = 2;
    break;
  case 8:
    value = value - m + 9;
    index = 3;
    break;
  case 9:
    if (value == 9) {
      value = 11;
      index = 0;
    } else {
      value = value - m + 9;
      index = 3;
    }
    break;
  }
  normalized nor;
  nor.value = value;
  nor.index = index;
  return nor;
}

inline int ess::getFlag(int64 block, int offset) {
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

/** Sieve for segment */
void ess::generate(vector<unsigned char> &buffer, int64 min, int64 max) {

  // Size in bytes of bits for store primes
  int segmentSize = 1 + ((max - min) / 20);

  // Data array. Are "char" but means "bytes"
  // vector<unsigned char> buffer(segmentSize, 0);
  buffer.clear();
  buffer.resize(segmentSize, 0);

  // data variables:
  int64 a, b, p, q, block, m;

  // Indices:
  int i, j, offset, flag;

  /* Separator array for 1,3,7,9
  Store deltas to increment 'a' and 'b' to numbers of the secuence:
  3,7,9,11,13,17,19,21....
  */
  // int s[] = {2, 4, 2, 2};
  int s[] = {2, 4, 2, 2};

  // Build filename
  // string filename = "primes_" + to_string(min) + "_" + to_string(max);

  // Build file:
  // ofstream ofs(filename, ios_base::binary);

  // Fill file with zeroes (means all numbers are prime)
  // fill(buffer, buffer + segmentSize, 0);

  // Get close to the next odd significant number
  a = 3;
  i = 1;

  // Main process
  while (true) {

    // Normalizer begin block

    // Obtenemos el último dígito y lo acercamos a algún número de la serie:
    b = min / a;
    m = b % 10;
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

    /*
        norm = normalizer(min / a);
        b = norm.value;
        j = norm.index;
        */
    while (true) {
      p = a * b;
      if (p > max)
        break;

      if (p > min) {

        // Mark bit block begin
        q = p - min;
        block = q / 20;
        offset = q - (20 * block);

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

        // flag = this->getFlag(block, offset);
        // int z = 1 << flag; // TODO: OPTIMIZAR ESTO
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
}

/** Return:
 * 1 if number is prime
 * 0 if number isn't prime
 * -1 if number is out of range
 * */
int ess::isPrime(vector<unsigned char> &buffer, int64 number, int64 min) {
  // Trivial answers:
  for (int i : this->trivialPrimerTable) {
    if (i == number)
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

  // Get byte to evaluate
  int64 block = ((number - min) / 20);

  // If number is out of range return -1
  if (block > buffer.size())
    return -1;

  // Get offset
  int offset = (number - min) - (20 * block);

  // Get byte to evaluate at offset
  int q = buffer[block];

  // Get bit position (flag)
  int flag = this->getFlag(block, offset);
  if (!(q & (1 << flag)))
    return 1;

  // Isn't prime, return 0.
  return 0;
}

void ess::showBuffer(unsigned char buffer[]) {}

int main(int argc, char *argv[]) {
  ess e1;
  kdTimer kt;

  vector<unsigned char> buffer;
  kt.start();
  int64 x = 100000000000000000000ull;
  int64 y = x + 1000;

  e1.generate(buffer, x, y);
  cout << kt.stop() << endl;

  int64 a, b;
  b = y - 1000;

  for (int64 j = b; j < y; j++) {
    if (e1.isPrime(buffer, j, x) == 1) {
      cout << p1000(j) << " " << j << endl;
    }
  }
}