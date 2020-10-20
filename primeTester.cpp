#include "primeTester.h"

// Constructor
primeTester::primeTester(int debugLevel) {
  this->debugLevel = debugLevel;
  kdTimer kt;

  // File size
  int sizeFile = MAX_INTEGER / 20;
  this->buffer.clear();
  this->buffer.resize(sizeFile, 0);

  kt.start();
  // Isn't there a database?
  if (!file_exists(DATABASE_FILE)) {
    this->createDataBase();
    cout << "Created data base on " << kt.snapshoot() << " seconds." << endl;
  } else {
    this->loadDataBase();
  }
}

// Build data base up to  (2^32)-1 prime numbers
void primeTester::createDataBase() {

  unsigned int a, b, p, i, j, rootMax, offset, block, flag;

  a = 3;
  b = 3;
  i = 1;
  j = 1;

  rootMax = sqrtl(MAX_INTEGER);

  cout << "Creating data base up to " << MAX_INTEGER << endl;

  while (true) {

    if (this->debugLevel > 1) {
      cout << "Mult of " << a << endl;
    }

    while (true) {
      p = a * b;
      if (p > MAX_INTEGER)
        break;

      // Mark bit block begin
      block = p / 20;
      offset = p - (20 * block);

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

      this->buffer[block] |= (1 << flag);
      // Mark bit block end

      b += this->deltas[j];
      j++;
      if (j == 4)
        j = 0;
    }
    a += this->deltas[i];
    i++;
    if (i == 4)
      i = 0;

    b = a;
    j = i;

    if (a > rootMax)
      break;
  }

  // Build file:
  ofstream ofs(DATABASE_FILE, ios_base::binary);

  // Save file
  ofs.write((char *)&this->buffer[0], this->buffer.size());
  ofs.flush();
  ofs.close();
}

void primeTester::reset() {
  this->lastPrime = 0;
  this->deltaPrime = 0;
}

unsigned int primeTester::next(unsigned int bottom) {
  unsigned int h = bottom;
  unsigned int r;
  if (bottom == 0)
    h = this->lastPrime;
  r = h + 1;
  if ((r & 1) == 0)
    r++;

  if (h < 11) {
    switch (h) {
    case 0:
      r = 2;
      break;

    case 2:
      r = 3;
      break;

    case 3:
      r = 5;
      break;

    case 5:
      r = 7;
      break;

    case 7:
      r = 11;
      break;
    }
    this->lastPrime = r;
    return r;
  }

  while (true) {

    if (this->test(r))
      break;
    r += 2;

    if (r >= MAX_INTEGER)
      return 0;
  }
  this->lastPrime = r;
  return r;
}

/**
 * Return a integer number wich accomplish with:
 * a)Is odd.
 * b)Finish on 1,3,7 or 9.
 * */

unsigned int primeTester::getNumber(unsigned int index) {
  unsigned int block = index / 8;
  unsigned int offset = index - (8 * block);
  unsigned int flag = 0;

  switch (offset) {
  case 0:
    flag = 1;
    break;
  case 1:
    flag = 3;
    break;
  case 2:
    flag = 7;
    break;
  case 3:
    flag = 9;
    break;
  case 4:
    flag = 11;
    break;
  case 5:
    flag = 13;
    break;
  case 6:
    flag = 17;
    break;
  case 7:
    flag = 19;
    break;
  }

  return (20 * block) + flag;
}

void primeTester::loadDataBase() {
  // File size
  unsigned int sizeFile = MAX_INTEGER / 20;

  vector<unsigned char> bf(sizeFile);
  ifstream ifs;
  ifs.open(DATABASE_FILE, ios_base::binary);
  ifs.read((char *)&bf[0], sizeFile);
  ifs.close();
  this->buffer.swap(bf);
}

bool primeTester::test(unsigned int number) {

  // is number <2 ... return false
  if (number < 2)
    return false;

  // Is number on a initial table?
  if (std::find(std::begin(this->initialTable), std::end(this->initialTable),
                number) != std::end(this->initialTable)) {
    return true;
  }

  //¿ Is number even?
  if ((number & 1) == 0)
    return false;

  // Check if is a 5 mult
  if ((number % 10) == 5)
    return false;

  // Find number on table
  unsigned int block;
  unsigned int offset;
  unsigned int flag;
  unsigned int q, w, e;

  block = number / 20;
  flag = number - (20 * block);

  switch (flag) {
  case 1:
    offset = 0;
    break;
  case 3:
    offset = 1;
    break;
  case 7:
    offset = 2;
    break;
  case 9:
    offset = 3;
    break;
  case 11:
    offset = 4;
    break;
  case 13:
    offset = 5;
    break;
  case 17:
    offset = 6;
    break;
  case 19:
    offset = 7;
    break;
  }

  q = this->buffer[block];
  w = 1 << offset;
  e = (q & w);

  return e != w;
}

bool primeTester::test(string number) {

  // Big integer representation
  mpz_class N(number), Root, A, B, P;
  int cycles = 0;
  kdProcessSpin kdps;

  // Int representation
  unsigned int n, prime;
  bool isBig = true;

  // Is number on a initial table?
  if (std::find(std::begin(this->initialTable), std::end(this->initialTable),
                N) != std::end(this->initialTable)) {
    return true;
  }

  // Check is is odd or even
  if (mpz_tstbit(N.get_mpz_t(), 0) == 0) {
    return false;
  }

  // Check if is 5 multiple
  if ((N % 10) == 5) {
    return false;
  }

  // Check if is big
  if (mpz_cmp_ui(N.get_mpz_t(), MAX_INTEGER) < 0) {
    isBig = false;
    n = N.get_ui();
  }

  if (!isBig) {
    return this->test(n);
  }

  if (debugLevel > 0) {
    cout << "This number is big!" << endl;
  }

  // Is big, so...
  // Take square root
  mpz_sqrt(Root.get_mpz_t(), N.get_mpz_t());

  // Check if root is even. Correct.
  if (mpz_tstbit(Root.get_mpz_t(), 0) == 0) {
    Root++;
  }

  if (debugLevel > 0) {
    cout << "Trying by module division..." << endl;
  }

  // Brute force division
  this->reset();
  prime = this->next(2);

  while (true) {
    if (prime > Root)
      return true; // si conseguimos un posible divisor(que no divide a N y es
                   // mayor que su raíz cuadrada entonces N es primo)
    mpz_mod_ui(A.get_mpz_t(), N.get_mpz_t(), prime);
    if (A == 0)
      return false;
    prime = this->next();
    if (prime > MAX_INTEGER)
      break;
    if (debugLevel > 0) {
      kdps.show();
    }
  }

  if (debugLevel > 0) {
    cout << "Trying by twin gears algorithm... May be slow." << endl;
  }

  // 549755813881

  // Big gear test
  A = Root;
  B = Root;
  while (true) {
    P = A * B;

    if (P == N)
      return false;

    if (P > N) {
      B -= 2;
    } else {
      A += 2;
    }
    if (B == 1)
      return true;

    if (debugLevel > 0) {
      kdps.show();
    }
  }

  return false;
}

/*
string primeTester::factorize(string number) {

  mpz_class root, n, r;
  mpz_set_str(n.get_mpz_t(), number.c_str(), 10);
  mpz_sqrt(root.get_mpz_t(), n.get_mpz_t());
  vector<unsigned int> factors;
  vector<bigFactorObject> objects;
  bool flag = false;
  bigFactorObject obj;
  string s;
  int i, j;

  unsigned int q = 0;

  while (true) {
    q = this->next(q);

    if (q > root) {
      factors.push_back(n.get_ui());
      break;
    }

    if (q > MAX_INTEGER) {
      break;
      // TODO: Show error...
    }
    while (true) {
      if (n == 1)
        break;
      mpz_mod_ui(r.get_mpz_t(), n.get_mpz_t(), q);
      if (r == 0) {
        factors.push_back(q);
        n /= q;
      } else {
        break;
      }
    }
  }

  for (i = 0; i < factors.size(); i++) {
    flag = false;
    for (j = 0; j < objects.size(); j++) {

      if (objects[j].base.get_str().compare(to_string(factors[i])) == 0) {
        objects[j].exponent++;
        flag = true;
        break;
      }
    }
    if (!flag) {
      bigFactorObject obj(factors[i], 1);
      objects.push_back(obj);
    }
  }

  // Sort factors
  sort(objects.begin(), objects.end(), bigFactorObjectCompare);

  i = 0;
  for (bigFactorObject obj : objects) {
    if (obj.exponent > 1) {
      s = s + obj.base.get_str() + "^" + to_string(obj.exponent);
    } else {
      s = s + obj.base.get_str();
    }
    i++;
    if (i < objects.size()) {
      s = s + " x ";
    }
  }

  return s;
}
*/

#ifndef PRIME_TESTER_LIB

int main(int argc, char *argv[]) {

  string number = "0";
  int command = -1;
  int debugLevel = 0;

  argumentsHandler argHdl(argc, argv);

  argHdl.add(argument(0, (char *)"n", (char *)"number",
                      (char *)"Number to evaluate", (char *)"n"));

  argHdl.add(argument(1, (char *)"c", (char *)"cli",
                      (char *)"Command line interface ask to evaluate...",
                      (char *)"n"));

  argHdl.add(argument(2, (char *)"d", (char *)"debug", (char *)"Debug level",
                      (char *)"N"));

  argHdl.add(argument(3, (char *)"f", (char *)"factorizer",
                      (char *)"factorizer n", (char *)"N"));


 


  int action = 0;
  while (action > -1) {
    action = argHdl.getAction();
    switch (action) {
    case 0:
      number = argHdl.value;
      command = 0;
      break;

    case 1:
      command = 1;
      break;

    case 2:
      argHdl.pvalue(&debugLevel);
      break;

    case 3:
      command = 2;
      break;
    }

    if (command < 0)
      exit(0);





  }

  primeTester pt(debugLevel);

  switch (command) {
  case 0:

    if (pt.test(number)) {
      cout << number << " is prime." << endl;
    } else {
      cout << number << " isn't prime." << endl;
    }
    break;

  case 1:
    cout << "Write number to evaluate + ENTER. Only ENTER to exit." << endl;
    while (true) {
      cin >> number;
      if (number == "")
        break;

      if (pt.test(number)) {
        cout << number << " is prime." << endl;
      } else {
        cout << number << " isn't prime." << endl;
      }
    }
    break;

  case 2:
    // cout << pt.factorize(number) << endl;
    break;

  default:
    break;
  }

  std::exit(0);
}

#endif
