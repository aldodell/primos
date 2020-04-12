#include "bigHalfGearFactorizer.h"

/* Número factorizado:
2^127-1-1
2*3^3*7^2*19*43*73*127*337*5419*92737*649657*77158673929

bigHalfGearFactorizer.out -n:170141183460469231731687303715884105726
2*3^3*7^2*19*43*73*127*337*5419*92737*649657*77158673929 (8968.79)
*/

bool compare(string sa, string sb) {
  mpz_class a, b;
  a = sa;
  b = sb;

  return mpz_cmp(a.get_mpz_t(), b.get_mpz_t()) < 0;
}

void bigHalfGearFactorizer::saveBigValue(mpz_class v) {

  this->bigValues.push_back(v.get_str());
  this->sortBigValues();
}

void bigHalfGearFactorizer::sortBigValues() {

  sort(this->bigValues.begin(), this->bigValues.end(), compare);

  ofstream ofs;
  ofs.open(BIG_VALUES_FILE, ios::trunc);
  for (string l : this->bigValues) {
    string r = l + "\n";
    ofs.write(r.c_str(), r.size());
  }

  ofs.flush();
  ofs.close();
}

void bigHalfGearFactorizer::loadBigValues() {
  ifstream ifs;
  ifs.open(BIG_VALUES_FILE, ios::in);
  string line;
  while (getline(ifs, line)) {
    this->bigValues.push_back(line);
  }
  ifs.close();
  this->sortBigValues();
}
bigHalfGearFactorizer::bigHalfGearFactorizer() {

  // Load big factors pre - sieved
  if (file_exists(BIG_VALUES_FILE)) {
    this->loadBigValues();
  } else {

    // 2^61-1
    saveBigValue(mpz_class("2305843009213693951"));
    // 2^89-1
    saveBigValue(mpz_class("618970019642690137449562111"));
    // 2^107-1
    saveBigValue(mpz_class("162259276829213363391578010288127"));
    // 2^127-1
    saveBigValue(mpz_class("170141183460469231731687303715884105727"));

    // Load values;
    this->loadBigValues();
  }
}

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

  // Find on database big numbers pre-sieved for improve speed
  if (n.get_str().length() > PRESIEVED_DIGITS) {
    for (int i = 0; i < this->bigValues.size(); i++) {
      pivot = this->bigValues[i];
      if (mpz_divisible_p(n.get_mpz_t(), pivot.get_mpz_t()) != 0) {
        mpz_divexact(n.get_mpz_t(), n.get_mpz_t(), pivot.get_mpz_t());
        this->factors.push_back(pivot);
      }
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
      if (mpz_divisible_p(n.get_mpz_t(), pivot.get_mpz_t()) == 0) {
        break;
      }
      mpz_divexact(n.get_mpz_t(), n.get_mpz_t(), pivot.get_mpz_t());
      mpz_sqrt(root.get_mpz_t(), n.get_mpz_t());
      this->factors.push_back(pivot);

      if (pivot.get_str().length() > PRESIEVED_DIGITS) {
        // if doesn't exists save it
        if (std::find(this->bigValues.begin(), this->bigValues.end(),
                      pivot.get_str()) == this->bigValues.end()) {
          this->saveBigValue(pivot);
        }
      }

      if (n == 1) {
        break;
      }
    }

    if (n == 1) {
      break;
    }

    if (pivot > root) {
      this->factors.push_back(n);
      if (n.get_str().length() > PRESIEVED_DIGITS) {
        // if doesn't exists save it
        if (std::find(this->bigValues.begin(), this->bigValues.end(),
                      n.get_str()) == this->bigValues.end()) {
          this->saveBigValue(n);
        }
      }
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

void bigHalfGearFactorizer::findMersenne(mpz_class p) {
  mpz_class mersenne, pivot, p2, k, root;

  // mersenne
  mpz_ui_pow_ui(mersenne.get_mpz_t(), 2, p.get_ui());
  mersenne--;
  mpz_sqrt(root.get_mpz_t(),
           mersenne.get_mpz_t()); // Find on database big numbers pre-sieved for
                                  // improve speed

  // Buscar el número si está en la base de datos
  if (mersenne.get_str().length() > PRESIEVED_DIGITS) {
    for (int i = 0; i < this->bigValues.size(); i++) {
      pivot = this->bigValues[i];
      if (mpz_divisible_p(mersenne.get_mpz_t(), pivot.get_mpz_t()) != 0) {
        mpz_divexact(mersenne.get_mpz_t(), mersenne.get_mpz_t(),
                     pivot.get_mpz_t());
        this->factors.push_back(pivot);
      }
    }
  }

  // Establecer los parámetros para búsqueda
  p2 = 2 * p;
  k = p2 + 1;

  while (true) {

    //¿Es divisible?
    if (mpz_divisible_p(mersenne.get_mpz_t(), k.get_mpz_t()) != 0) {
      this->factors.push_back(k); // Lo pasamos como factor
      gmp_printf("%Zd\n", k.get_mpz_t());

      // Evaluamos si tenemos el número en la base de datos. Sino lo incluímos
      if (k.get_str().length() > PRESIEVED_DIGITS) {
        // if doesn't exists save it
        if (std::find(this->bigValues.begin(), this->bigValues.end(),
                      k.get_str()) == this->bigValues.end()) {
          this->saveBigValue(k);
        }
      }

      mpz_divexact(mersenne.get_mpz_t(), mersenne.get_mpz_t(), k.get_mpz_t());
      if(mersenne==1) {break;}

      mpz_sqrt(
          root.get_mpz_t(),
          mersenne.get_mpz_t()); // Find on database big numbers pre-sieved for

          
    }

    k += p2;
    if (k > root) {
      this->factors.push_back(mersenne);
      // Evaluamos si tenemos el número en la base de datos. Sino lo incluímos
      if (k.get_str().length() > PRESIEVED_DIGITS) {
        // if doesn't exists save it
        if (std::find(this->bigValues.begin(), this->bigValues.end(),
                      k.get_str()) == this->bigValues.end()) {
          this->saveBigValue(k);
        }
      }

      break;
    }
  }
}

#ifndef BIG_HALF_GEAR_FACTORIZER_LIB

int main(int argc, char *argv[]) {

  // argument handler:
  argumentsHandler argHdl(argc, argv);
  bigHalfGearFactorizer gf;

  int action = 0;
  int debugLevel = 0;
  mpz_class n;
  kdTimer kt;

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
      n = argHdl.value;
      kt.start();
      gf.find(n);
      cout << gf.toString() << " (" << kt.stop() << ")" << endl;
      break;
    case 1:
      argHdl.pvalue(&debugLevel);
      break;
    case 2:
      n = argHdl.value;
      kt.start();
      gf.findMersenne(n);
      cout << gf.toString() << " (" << kt.stop() << ")" << endl;

      break;
    }
  }

  return 0;
}

#endif