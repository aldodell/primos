#include "bigGearsFactorizer.h"



bigGearsFactorizer::bigGearsFactorizer(primeTester *tester) {
  this->tester = tester;
}

bigGearsFactorizer::~bigGearsFactorizer() {}

void bigGearsFactorizer::clear() { this->factors.clear(); }

char bigGearsFactorizer::lastDigit(mpz_class n) {
  string s = n.get_str();
  char d = s[s.size() - 1];
  return d;
}

void bigGearsFactorizer::find(mpz_class n) {
  mpz_class t1, a, b, p, q;
  unsigned int r, rMax;

  // Determine if number is divisible by 2
  while (true) {
    if (mpz_tstbit(n.get_mpz_t(), 0) == 1)
      break;
    n /= 2;
    this->factors.push_back(2);
  }

  r = 3;
  this->tester->reset();

  while (true) {
    mpz_mod_ui(q.get_mpz_t(), n.get_mpz_t(), r);
    if (q == 0) {
      this->factors.push_back(r);
      n /= r;
    } else {
      rMax = r;
      r = this->tester->next(r);
      if (r == 0) {
        break;
      }
    }
    if (n == 1) {
      return;
    }
  }

  // Get squere root
  mpz_sqrt(a.get_mpz_t(), n.get_mpz_t());

  if (a < rMax) {
    this->factors.push_back(n);
    return;
  }

  // Check a is odd:
  if (mpz_tstbit(a.get_mpz_t(), 0) == 0) {
    a--;
  }
  b = a;

  while (true) {
    if (b < rMax) {
      this->factors.push_back(n);
      return;
    }
    p = a * b;
    if (p == n) {
      if (b == 1) {
        this->factors.push_back(a);
        return;
      }
      this->find(a);
      this->find(b);
      return;
    }
    if (p > n) {
      b -= 2;
    } else if (p < n) {
      a += 2;
    }
  }
}

string bigGearsFactorizer::toString() {
  vector<bigFactorObject> objects;
  bool flag = false;
  bigFactorObject obj;
  string s;
  int i, j;

  for (i = 0; i < this->factors.size(); i++) {
    flag = false;
    for (j = 0; j < objects.size(); j++) {

      if (objects[j].base.get_str().compare(this->factors[i].get_str()) == 0) {
        objects[j].exponent++;
        flag = true;
        break;
      }
    }
    if (!flag) {
      bigFactorObject obj(this->factors[i], 1);
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

#ifndef BIG_GEARS_FACTORIZER_LIB

int main(int argc, char *argv[]) {

  // argument handler:
  argumentsHandler argHdl(argc, argv);
  primeTester *pt(0);
  bigGearsFactorizer gf(pt);
  int action = 0;
  int debugLevel = 0;
  mpz_class n;

  argHdl.add(argument(0, (char *)"n", (char *)"number",
                      (char *)"Number to be factorized", (char *)"N"));
  argHdl.add(argument(1, (char *)"d", (char *)"debug", (char *)"Debug level",
                      (char *)"N"));

  while (action > -1) {
    action = argHdl.getAction();
    switch (action) {
    case 0:
      // argHdl.pvalue();
      n = argHdl.value;
      break;
    case 1:
      argHdl.pvalue(&debugLevel);
      break;
    }
  }

  // gf.debugLevel = debugLevel;
  kdTimer kt;
  kt.start();
  gf.find(n);
  cout << gf.toString() << " (" << kt.stop() << ")" << endl;

  return 0;
}

#endif