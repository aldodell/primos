#include "aldo.h"

void aldo() {

  primeTester pt(0);

  bigGearsFactorizer bgf(&pt);

  unsigned int a = 0;
  mpz_class m;
  string s, r, t;

  pt.reset();

  cout << " <!DOCTYPE html>"
          "<html>"
          "<head>"
          "  <title>Mersenne experiments</title>"
          "</head>"
          "<body>"
       << endl;

  while (true) {
    a = pt.next(a);
    if (a > 130)
      break;

    s = mersenne(a);
    m = s;
    bgf.clear();
    bgf.find(m);
    t = bgf.toString();

    if (bgf.factors.size() == 1) {

      r = "<div>"
          "<b>2<sup>%d</sup>-1 = %Zd</b>"
          "<div>Factors = %s</div>"
          "</div>"
          "<br>";
    } else {

      r = "<div>"
          "2<sup>%d</sup>-1 = %Zd"
          "<div>Factors =%s</div>"
          "</div>"
          "<br>";
    }

    gmp_printf(r.c_str(), a, m.get_mpz_t(), t.c_str());
    cout.flush();
  }

  cout << "</body></html>" << endl;
}

void aldo2() {

  mpz_class k, p, two, q;
  int i, r;
  p = 2;
  two = 2;
  string rr;

  for (i = 0; i < 10; i++) {

    k = two;

    for (q = 0; q < (p - 1); q++) {
      k = k * two;
    }

    k = k - 1;
    r = mpz_probab_prime_p(k.get_mpz_t(), 20);

    // mpz_pow_ui(k.get_mpz_t(), two.get_mpz_t(), p.get_ui());
    // k = k - 1;
    r = mpz_probab_prime_p(k.get_mpz_t(), 20);
    gmp_printf("2 ^ %Zd - 1 = %Zd. R=%d \r\n", p.get_mpz_t(), k.get_mpz_t(), r);
    p = k;
  }
}

void aldo3() {

  int exp = 1;
  int max, k, n, r, f, p;
  max = 126;
  mpz_class f1, f2;

  for (exp = 1; exp < 8; exp++) {
    for (n = 2; n <= max; n += 2) {
      p = (int)pow(2, exp);
      r = n % p;
      if (r == 0) {
        f = n / p;
        printf("%d: 2^%d x %d\n", n, exp, f);
      }
    }
  }

  mpz_fac_ui(f1.get_mpz_t(), 126);
  f1 += 1;
  f2 = 127;
  mpz_mod(f1.get_mpz_t(), f1.get_mpz_t(), f2.get_mpz_t());

  gmp_printf("%Zd\n", f1.get_mpz_t());

  mpz_ui_pow_ui(f1.get_mpz_t(), 2, 127);
  f1++;
  f2 = 3;
  mpz_mod(f1.get_mpz_t(), f1.get_mpz_t(), f2.get_mpz_t());
  gmp_printf("%Zd\n", f1.get_mpz_t());

  mpz_ui_pow_ui(f1.get_mpz_t(), 2, 127);
  f1--;
  cout << f1.get_str(2) << endl;
  cout << f1.get_str(2).length() << endl;

  /*
     mpz_ui_pow_ui(f1.get_mpz_t(), 2, f1.get_ui());
     f1--;
     cout << f1.get_str(2) << endl;
    */

  string s1 = "1";
  for (n = 1; n < 128; n++) {
    mpz_set_str(f1.get_mpz_t(), s1.c_str(), 2);
    gmp_printf("%d : %Zd\n", n, f1.get_mpz_t());
    s1 = s1 + "1";
  }
}

int main(int argc, char *argv[]) { aldo3(); }