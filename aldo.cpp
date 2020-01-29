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

int main(int argc, char *argv[]) { aldo(); }