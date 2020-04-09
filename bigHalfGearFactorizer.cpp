#include "bigHalfGearFactorizer.h"

/* Número factorizado:
2^127-1-1
2*3^3*7^2*19*43*73*127*337*5419*92737*649657*77158673929

bigHalfGearFactorizer.out -n:170141183460469231731687303715884105726
2*3^3*7^2*19*43*73*127*337*5419*92737*649657*77158673929 (8968.79)
*/

/*
Factorizador de números grandes con detección de primariedad determinista
No usa base de datos previos
*/

void bigHalfGearFactorizer::find(mpz_class n) {
  mpz_class pivot, mod, root;

  if (n < 2) {
    return;
  }

  // Filter "2" factors (for discard parity)
  while (true) {
    if (mpz_tstbit(n.get_mpz_t(), 0) == 0) {
      n /= 2;
      this->factors.push_back(2);
    } else {
      break;
    }
  }

  // If reached end, exits.
  if (n == 1)
    return;

  // Next pivot value
  pivot = 3;

  // square root of number to be factorized
  mpz_sqrt(root.get_mpz_t(), n.get_mpz_t());

  while (true) {

    while (true) {
      // mpz_mod(mod.get_mpz_t(), n.get_mpz_t(), pivot.get_mpz_t());
      // if (mod > 0) {
      if (mpz_divisible_p(n.get_mpz_t(), pivot.get_mpz_t()) == 0) {
        break;
        // ESTABA AQUI:  mpz_sqrt(root.get_mpz_t(), n.get_mpz_t());
      }
      mpz_divexact(n.get_mpz_t(), n.get_mpz_t(), pivot.get_mpz_t());
      mpz_sqrt(root.get_mpz_t(), n.get_mpz_t());

      // n /= pivot;
      this->factors.push_back(pivot);
      if (n == 1) {
        break;
      }
    }

    if (n == 1) {
      break;
    }

    if (pivot > root) {
      this->factors.push_back(n);
      break;
    }

    pivot += 2;
  }
}

void bigHalfGearFactorizer::clear() { this->factors.clear(); }

string bigHalfGearFactorizer::toString() {
  vector<bigFactorObject> objects;
  bool flag = false;
  bigFactorObject obj;
  string s;
  int i, j;

  if (this->factors.size() == 0) {
    return "";
  }

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
      s = s + "*";
    }
  }

  return s;
}

#ifndef BIG_HALF_GEAR_FACTORIZER_LIB

int main(int argc, char *argv[]) {

  // argument handler:
  argumentsHandler argHdl(argc, argv);
  bigHalfGearFactorizer gf;

  int action = 0;
  int debugLevel = 0;
  mpz_class n;

  argHdl.add(argument(0, (char *)"n", (char *)"number",
                      (char *)"Number to be factorized", (char *)"N"));
  argHdl.add(argument(1, (char *)"d", (char *)"debug", (char *)"Debug level",
                      (char *)"N"));

  argHdl.add(argument(2, (char *)"m", (char *)"mersenne",
                      (char *)"Factorize a mersenne. 2^m-1", (char *)"N"));

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
    case 2:
      n = argHdl.value;
      mpz_ui_pow_ui(n.get_mpz_t(), 2, n.get_ui());
      n--;
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