/**
 * Some functions using ONIs Algebra (By Eleazar Tirado)
 * */

#include "oni.h"

inline int mygcd(int a, int b) {
  if (b == 0)
    return a;
  return mygcd(b, a % b);
}

mpz_class oni_sum(mpz_class a, mpz_class b) {
  mpz_class i; // counter
  mpz_class s; // sum
  for (i = a; i <= b; i += 2) {
    s += i;
  }
  return s;
}

void oni_primarity(mpz_class z) {
  kdProcessBenchmark benckmark;
  mpz_class a, b, q, r, s;
  a = 3;
  b = 2 * z - 1;
  q = z * z;
  s = (q + 1) / 2;

  benckmark.cyclesForStep = 10000000;
  printf("Calculating first ONI serie.\n");
  benckmark.start();
  r = (((a + b) / 2) * (((b - a) / 2) + 1)); //
  benckmark.stop();

  printf("Calculating primarity.\n");
  benckmark.start();

  while (true) {
    benckmark.tick();
    gmp_printf("%Zd\t%Zd\t%Zd\n", a.get_mpz_t(), b.get_mpz_t(), r.get_mpz_t());
    if (r == q) {
      gmp_printf("%Zd isn't prime. a=%Zd, b=%Zd.\n", z.get_mpz_t(),
                 a.get_mpz_t(), b.get_mpz_t());
      break;
    }

    while (r > q) {
      r -= a;
      a += 2;
    }

    while (r < q) {
      b += 2;
      r += b;
    }

    if (a > s) {
      gmp_printf("%Zd is prime. a=%Zd, b=%Zd.\n", z.get_mpz_t(), a.get_mpz_t(),
                 b.get_mpz_t());
      break;
    }
  }
  benckmark.stop();
}

void oni_test1(unsigned int a, unsigned int b) {

  unsigned int p;
  unsigned int i;
  unsigned int j;
  bigHalfGearFactorizer bf;
  mpz_class q = 2;

  mpz_class lt, m, n, f, g;
  string s[]{"no primo", "probablemente primo", "primo"};

  gmp_printf("p;lt;prime\n");
  for (i = a; i < b; i++) {
    p = mersenneExponents[i];
    // mpz_nextprime(q.get_mpz_t(), q.get_mpz_t());
    mpz_ui_pow_ui(m.get_mpz_t(), 2, p);
    m--;
    lt = 2 * m - 1;
    j = mpz_probab_prime_p(lt.get_mpz_t(), 15);
    bf.clear();
    bf.find(lt);
    gmp_printf("2^%d-1;2M-1 *%s*;%s.", p, s[j].c_str(),
               bf.toString(true).c_str());

    sort(bf.factors.begin(), bf.factors.end());
    for (int i = 0; i < bf.factors.size(); i++) {
      f = bf.factors[i];
      mpz_mod_ui(n.get_mpz_t(), f.get_mpz_t(), 22);
      g = f / 22;
      gmp_printf("\n\t%Zd=2*11*%Zd+%Zd ", f.get_mpz_t(), g.get_mpz_t(),
                 n.get_mpz_t());
    }
    printf("\n");
  }
}

/** Este test busca los números de Mersenne con p terminados en 7 y prueba
 * si 2M-1 es divisibles por 11
 * */
void oni_test2(int a, int b) {
  int i;
  int p;
  mpz_class m;
  for (i = 0; i < 51; i++) {
    p = mersenneExponents[i];

    if (p % 10 == a) {
      mpz_ui_pow_ui(m.get_mpz_t(), 2, p);
      m--;
      m = 2 * m - 1;

      if (mpz_divisible_ui_p(m.get_mpz_t(), b) != 0) {
        printf("2*(2^%d-1)-1 es divisible por %d.\n", p, b);
      } else {
        printf("2*(2^%d-1)-1 NO es divisible por %d.\n", p, b);
      }
    }
  }
}

string findPower(mpz_class n) {
  //, mpz_class &x, mpz_class &y
  mpz_class p, e, b;

  b = 2;
  do {
    p = 1;
    e = 0;
    while (p < n) {
      p *= b;
      e++;
      if (p == n) {
        char s[32];
        sprintf(s, "%lu^%lu", b.get_ui(), e.get_ui());
        return string(s);
      }
    }
    b++;
  } while ((b * b) <= n);
  return "";
}

void findPower(mpz_class n, mpz_class &x, mpz_class &y) {
  mpz_class p, e, b;

  b = 2;
  do {
    p = 1;
    e = 0;
    while (p < n) {
      p *= b;
      e++;
      if (p == n) {
        x = b;
        y = e;
        return;
      }
    }
    b++;
  } while ((b * b) <= n);
  return;
}

inline void findPower(mpz_class n, int &x, int &y) {
  mpz_class p, e, b, b2;
  do {
    p = 1;
    e = 0;
    while (p < n) {
      p *= b;
      e++;
      if (p == n) {
        x = b.get_ui();
        y = e.get_ui();
        return;
      }
    }
    b++;
  } while ((b * b) <= n);
  return;
}

void oni_worker_3(int x, int y, mpz_class min, mpz_class max, int bMin, int id,
                  string &result, int &threadSum) {
  int a, b, c, d;
  mpz_class p1, p2, p, border;
  kdTimer kdtimer;

  mpz_ui_pow_ui(p.get_mpz_t(), x, y);
  mpz_root(border.get_mpz_t(), max.get_mpz_t(), bMin);
  kdtimer.start();
  a = 2;
  do {
    b = bMin;
    do {
      mpz_ui_pow_ui(p1.get_mpz_t(), a, b);
      if (p1 > max) {
        break;
      }
      if (p1 >= min) {
        p2 = p - p1;
        if (mpz_perfect_power_p(p2.get_mpz_t())) {
          findPower(p2, c, d);
          if (!(a % c == 0 || c % a == 0)) {
            char s[127];
            sprintf(s, "%d^%d = %d^%d + %d^%d. Time:%.4f", x, y, a, b, c, d,
                    kdtimer.stop());
            result = string(s);
            goto oni_worker_exit;
          }
        }
      }
      b++;
    } while (true);
    a++;
    if (a > border) {
      break;
    }
  } while (true);

oni_worker_exit:
  threadSum++;
  return;
}

void oni_worker_3b(int x, int y, mpz_class min, mpz_class max, int bMin, int id,
                   string &result, int &threadSum) {
  int a, b, c, d, aMin;
  mpz_class p1, p2, p, t;
  kdTimer kdtimer;

  mpz_ui_pow_ui(p.get_mpz_t(), x, y);
  kdtimer.start();
  aMin = 2;

  a = aMin;
  b = bMin;

  do {
    do {
      if (result != "") {
        goto l1;
      }
      mpz_ui_pow_ui(p1.get_mpz_t(), a, b);
      if (p1 > max) {
        if (a == aMin) {
          goto l1;
        } else {
          break;
        }
      }
      if (p1 >= min) {
        p2 = p - p1;
        if (mpz_perfect_power_p(p2.get_mpz_t()) != 0) {
          if (mygcd(a, x) == 1) {
            findPower(p2, c, d);
            if (mygcd(a, c) == 1) {
              char s[127];
              sprintf(s, "%d^%d = %d^%d + %d^%d . Time:%.4f", x, y, a, b, c, d,
                      kdtimer.stop());
              result = string(s);
              goto l1;
            }
          }
        }
      }
      a++;
    } while (true);
    a = aMin;
    b++;
  } while (true);
l1:
  //  gmp_printf("Closing thread %d, min=%Zd, max=%Zd\n", threadSum,
  //  min.get_mpz_t(),
  //             max.get_mpz_t());
  threadSum++;
  return;
}

/***
 * Este modelo inicia con 2^2 y recorre 3^2, 4^2, 5^2 y así...
 * hasta que se consiga una potencia del lado derecho
 * o que la potencia del lado izquiero sea mayor al centro
 * */
void oni_worker_4(int x, int y, int e, string &result, int &threadSum) {
  mpz_class p, m, p1, p2;
  int a, b, c, d;
  kdTimer timer;

  mpz_ui_pow_ui(p.get_mpz_t(), x, y); // Initial power
  m = p / 2;                          // ONI's middle.

  p1 = 0;
  p2 = 0;
  a = 2;
  b = 2;
  c = 0;
  d = 0;

  timer.start();
  while (true) {
    while (true) {
      mpz_ui_pow_ui(p1.get_mpz_t(), a, b);
      if (p1 > m) {
        if (a == 2) {
          goto exit;
        } else {
          break;
        }
      }
      p2 = p - p1;
      findPower(p2, c, d);
      if (c > 0) {
        char s[127];
        sprintf(s, "%d^%d = %d^%d + %d^%d. Time:%.4f", x, y, a, b, c, d,
                timer.stop());
        result = string(s);
        goto exit;
      }
      a++;
    }
    a = 2;
    b++;
  }
exit:
  threadSum++;
  return;
}

void oni_worker(int x, int y, mpz_class min, mpz_class max, int bMin, int id,
                string &result, int &threadSum) {
  unsigned int a, b;
  mpz_class p1, p2, p, m;
  kdTimer kdtimer;

  mpz_ui_pow_ui(p.get_mpz_t(), x, y);
  m = p / 2;

  a = 2;
  b = bMin;

  kdtimer.start();
  do {
    do {
      mpz_ui_pow_ui(p1.get_mpz_t(), a, b);
      if (p1 >= min) {
        if (p1 > max) {
          break;
        }
        p2 = p - p1;
        if (mpz_perfect_power_p(p2.get_mpz_t()) != 0) {
          if (mpz_divisible_ui_p(p1.get_mpz_t(), x) == 0) {
            char s[127];
            sprintf(s, "%d^%d = %d^%d + %s. Time:%.4f", x, y, a, b,
                    findPower(p2).c_str(), kdtimer.stop());
            result = string(s);
            goto oni_worker_exit;
          }
        }
      }
      b++;
    } while (true);
    a++;
    b = bMin;
    mpz_ui_pow_ui(p1.get_mpz_t(), a, b);
    if (p1 > max) {
      break;
    }
  } while (true);
oni_worker_exit:
  threadSum++;
  return;
}

void oni_finder(unsigned int x, unsigned int y, unsigned int bMin,
                int threadsQuantity) {
  int threadSum = 0;
  unsigned int i;
  mpz_class p, m, r, max, min;
  vector<thread> threads;
  string result = "";

  mpz_ui_pow_ui(p.get_mpz_t(), x, y);
  m = p / 2;
  r = m / threadsQuantity;

  // Left side
  for (i = 0; i < threadsQuantity; i++) {
    min = i * r;
    max = min + r;
    threads.push_back(thread(oni_worker, x, y, min, max, bMin, i, ref(result),
                             ref(threadSum)));
  }

  // Right side
  for (i = 0; i < threadsQuantity; i++) {
    min = (i * r) + m;
    max = min + r;
    threads.push_back(thread(oni_worker, x, y, min, max, bMin, i, ref(result),
                             ref(threadSum)));
  }

  while (threadSum < (2 * threadsQuantity)) {
  };

  for (thread &t : threads) {
    if (t.joinable()) {
      t.detach();
    }
  }

  if (result.length() == 0) {
    char s[127];
    sprintf(s, "%d^%d not match.", x, y);
    result = string(s);
  }

  printf("%s\n", result.c_str());
}

void oni_loop(unsigned int x, unsigned int bMin, int threadsQuantity) {
  unsigned int y = 0;
  while (y < 128) {
    y++;
    oni_finder_3(x, y, bMin, threadsQuantity);
    this_thread::yield();
  }
}

void oni_worker_2(int x, int y, mpz_class min, mpz_class max, int id,
                  string &result, int &threadSum) {

  mpz_class p, p1, p2, m, gcd;
  mpz_class a, b, c, d;
  mpz_ui_pow_ui(p.get_mpz_t(), x, y);
  m = p / 2;
  string l, r, R;
  kdTimer timer;

  timer.start();
  for (p1 = min; p1 <= max; p1++) {
    if (mpz_perfect_power_p(p1.get_mpz_t()) != 0) {
      p2 = p - p1;
      if (mpz_perfect_power_p(p2.get_mpz_t()) != 0) {
        findPower(p1, a, b);
        findPower(p2, c, d);
        mpz_gcd(gcd.get_mpz_t(), a.get_mpz_t(), c.get_mpz_t());
        if (gcd < 2) {
          char s[32];
          gmp_sprintf(s, "%d^%d = %Zd^%Zd + %Zd^%Zd. Time=%.3f", x, y,
                      a.get_mpz_t(), b.get_mpz_t(), c.get_mpz_t(),
                      d.get_mpz_t(), timer.stop());
          result = string(s);
          goto oni_worker_2_exit;
        }
      }
    }
  }
oni_worker_2_exit:
  threadSum++;
  return;
}

void oni_finder_2(unsigned int x, unsigned int y, int threadsQuantity) {
  int threadSum = 0;
  unsigned int i;
  mpz_class p, m, r, max, min;
  vector<thread> threads;
  string result = "";

  mpz_ui_pow_ui(p.get_mpz_t(), x, y);
  m = p / 2;
  r = m / threadsQuantity;

  // Left side
  for (i = 0; i < threadsQuantity; i++) {
    min = i * r;
    max = min + r;
    threads.push_back(
        thread(oni_worker_2, x, y, min, max, i, ref(result), ref(threadSum)));
  }

  // Right side
  for (i = 0; i < threadsQuantity; i++) {
    min = (i * r) + m;
    max = min + r;
    threads.push_back(
        thread(oni_worker_2, x, y, min, max, i, ref(result), ref(threadSum)));
  }

  while (threadSum < (2 * threadsQuantity)) {
  };

  for (thread &t : threads) {
    if (t.joinable()) {
      t.detach();
    }
  }

  if (result.length() == 0) {
    char s[127];
    sprintf(s, "%d^%d not match.", x, y);
    result = string(s);
  }

  printf("%s\n", result.c_str());
}

void oni_finder_3(unsigned int x, unsigned int y, unsigned int bMin,
                  int threadsQuantity) {
  int threadSum = 0;
  unsigned int i;
  mpz_class p, m, r, max, min;
  vector<thread> threads;
  string result = "";

  mpz_ui_pow_ui(p.get_mpz_t(), x, y);
  m = p / 2;
  r = m / threadsQuantity;

  // Left side
  for (i = 0; i < threadsQuantity; i++) {
    min = i * r;
    max = min + r;
    threads.push_back(thread(oni_worker_3b, x, y, min, max, bMin, i,
                             ref(result), ref(threadSum)));
  }

  // Right side
  for (i = 0; i < threadsQuantity; i++) {
    min = (i * r) + m;
    max = min + r;
    threads.push_back(thread(oni_worker_3b, x, y, min, max, bMin, i,
                             ref(result), ref(threadSum)));
  }

  while (result == "" && threadSum < (2 * threadsQuantity)) {
    this_thread::yield();
  };

  for (thread &t : threads) {
    if (t.joinable()) {
      t.join();
    }
  }

  if (result.length() == 0) {
    char s[127];
    sprintf(s, "%d^%d not match.", x, y);
    result = string(s);
  }

  printf("%s\n", result.c_str());
}

/*
void printPlaintext(mpz_t plaintext) {
   size_t count = 1024;
   char *buffer = (char *)calloc(count, sizeof(char));

   mpz_export((void*)buffer, &count, 1, sizeof( char), 1, 0, plaintext);
   printf("%s\n", buffer);
}


cstring *bn_getvch(const mpz_t v)
{

        size_t sz;
        char *buf = mpz_export(NULL, &sz, -1, 1, 1, 0, v);

*/

/*
struct PowerData {
  char x, y;
  char buffer[16] = {0};

  PowerData(unsigned int x, unsigned int y, mpz_class p) {
    this->x = x;
    this->y = y;
    // void * mpz_export (void *rop, size_t *countp, int order, size_t size, int
    // endian, size_t nails, const mpz_t op)
    size_t size;

    void *buf = mpz_export(NULL,  // rop
                           &size, // size_t countp
                           1,     // order
                           1,     // size_t size
                           1,     // endian
                           0,     // size_t nails
                           p.get_mpz_t());

    memcpy(this->buffer, buf, size);
    free(buf);
  }
};
*/

/*
void write(const std::string& file_name, s& data)
{
  std::ofstream out(file_name.c_str());
  out.write(reinterpret_cast<char*>(&s), sizeof(s));
}

void read(const std::string& file_name, s& data)
{
  std::ifstream in(file_name.c_str());
  in.read(reinterpret_cast<char*>(&s), sizeof(s));
}
*/

struct PowerData {
  unsigned char x;
  unsigned char y;
  mpz_class p;
  PowerData(unsigned int x, unsigned int y, mpz_class p) {
    this->p = p;
    this->x = x;
    this->y = y;
  }
  bool operator<(const PowerData &pd) const { return (this->p < pd.p); }
  static PowerData empty() {
    PowerData pd(0, 0, 0);
    return pd;
  }
};

struct OniMatch {
  // o = p1 + p2 = x^y = a^b + c^d
  PowerData p1 = PowerData::empty(); // Left side
  PowerData p2 = PowerData::empty(); // Right side
  PowerData o = PowerData::empty();  // Origin

  static OniMatch empty() {
    return OniMatch(PowerData::empty(), PowerData::empty(), PowerData::empty());
  };

  OniMatch() {
    this->o = PowerData::empty();
    this->p1 = PowerData::empty();
    this->p2 = PowerData::empty();
  }

  OniMatch(PowerData o, PowerData p1, PowerData p2) {
    this->o = o;
    this->p1 = p1;
    this->p2 = p2;
  }
};

void buildPowerData(unsigned int a, unsigned int b) {
  string file_name = "power-data.bin";
  vector<PowerData> powers;
  mpz_class p, limit;
  int x, y, i;
  mpz_ui_pow_ui(limit.get_mpz_t(), a, b);

  x = 2;
  y = 2;
  i = 0;

  do {
    do {
      mpz_ui_pow_ui(p.get_mpz_t(), x, y);
      if (p > limit) {
        if (y == 2) {
          goto finish;
        }
        break;
      }

      if (mpz_perfect_power_p(mpz_class(x).get_mpz_t()) == 0) {
        powers.emplace_back(x, y, p);
        //        gmp_printf("%d ^ %d = %Zd\n", x, y, p.get_mpz_t());
        i++;
      }
      y++;

    } while (true);
    y = 2;
    x++;
  } while (true);
finish:
  printf("Count=%d\nSorting vector... \n", i);

  // Sort powers by results
  sort(powers.begin(), powers.end());

  printf("Saving file... \n");

  size_t sz;
  void *buf;
  ofstream out(file_name.c_str());
  for (PowerData pd : powers) {

    // Convert
    mpz_export(buf, // rop
               &sz, // size_t countp
               1,   // order
               1,   // size_t size
               1,   // endian
               0,   // size_t nails
               pd.p.get_mpz_t());

    // Write x and y on x^y
    // char pdx[1] = {(char)pd.x};
    out.write(reinterpret_cast<char *>(&pd.x), 1);
    out.write(reinterpret_cast<char *>(&pd.y), 1);

    // write size:
    out.write(reinterpret_cast<char *>(&sz), 1);
    // Write representation:
    out.write(reinterpret_cast<char *>(&buf), sz);
  }
  out.flush();
  out.close();

  return;
}

OniMatch searchONIByPowerData(unsigned int x, unsigned int y,
                              vector<PowerData> &data) {
  mpz_class p, p1, p2, m;
  mpz_ui_pow_ui(p.get_mpz_t(), x, y);
  m = p / 2;

  for (PowerData &pd : data) {
    if (pd.p > m) {
      break;
    }

    p1 = pd.p;
    p2 = p - p1;

    for (PowerData &pdx : data) {
      if (pdx.p == p2) {
        return OniMatch(PowerData(x, y, p), pd, pdx);
      }
    };
  }
  return OniMatch::empty();
}

int main(int argc, char *argv[]) {
  argumentsHandler argHdl(argc, argv);

  int debugLevel;
  int action;
  int bMin, x, y, threads;
  mpz_class a, b, c, d;

  argHdl.add(argument(0, (char *)"debug", (char *)"debug",
                      (char *)"Debug level", (char *)"N"));

  argHdl.add(argument(1, (char *)"a", (char *)"A", (char *)"a parameter",
                      (char *)"N"));

  argHdl.add(argument(2, (char *)"b", (char *)"B", (char *)"b parameter",
                      (char *)"N"));

  argHdl.add(argument(3, (char *)"c", (char *)"C", (char *)"c parameter",
                      (char *)"N"));

  argHdl.add(argument(4, (char *)"d", (char *)"D", (char *)"d parameter",
                      (char *)"N"));

  argHdl.add(argument(5, (char *)"bmin", (char *)"bMin",
                      (char *)"Minimun b on a^b", (char *)"N"));

  argHdl.add(
      argument(6, (char *)"x", (char *)"X", (char *)"x  on x^y", (char *)"N"));

  argHdl.add(
      argument(7, (char *)"y", (char *)"Y", (char *)"y  on x^y", (char *)"N"));

  argHdl.add(argument(8, (char *)"threads", (char *)"THREADS",
                      (char *)"Threads quantity", (char *)"N"));

  argHdl.add(argument(9, (char *)"finder", (char *)"FINDER",
                      (char *)"ONI finder: x,y,bmin,threads", (char *)"N"));

  argHdl.add(argument(10, (char *)"loop", (char *)"LOOP",
                      (char *)"ONI finder looping: x, bmin,threads",
                      (char *)"N"));

  argHdl.add(argument(11, (char *)"finder2", (char *)"FINDER2",
                      (char *)"ONI finder: x,y,threads", (char *)"N"));

  argHdl.add(argument(12, (char *)"finder3", (char *)"FINDER3",
                      (char *)"ONI finder: x,y,bmin,threads", (char *)"N"));

  argHdl.add(argument(13, (char *)"powerbuild", (char *)"POWERBUILD",
                      (char *)"limit: x^y", (char *)"N"));

  while (action > -1) {
    action = argHdl.getAction();

    switch (action) {

    case 0:
      argHdl.pvalue(&debugLevel);
      break;

    case 1:
      a = argHdl.value;
      break;

    case 2:
      b = argHdl.value;
      break;

    case 3:
      c = argHdl.value;
      break;

    case 4:
      d = argHdl.value;
      break;

    case 5:
      argHdl.pvalue(&bMin);
      break;

    case 6:
      argHdl.pvalue(&x);
      break;

    case 7:
      argHdl.pvalue(&y);
      break;

    case 8:
      argHdl.pvalue(&threads);
      break;

    case 9:
      oni_finder(x, y, bMin, threads);
      break;

    case 10:
      oni_loop(x, bMin, threads);
      break;

    case 11:
      oni_finder_2(x, y, threads);
      break;

    case 12:
      oni_finder_3(x, y, bMin, threads);
      break;

    case 13:
      buildPowerData((unsigned int)x, (unsigned int)y);
      break;
    }
  }
  exit(0);
}