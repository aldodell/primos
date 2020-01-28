#include "tirado3.h"

mpz_class a, b;
bigGearsFactorizer bgf;

string tirado3(int exponent) {

  // stage 1
  mpz_ui_pow_ui(a.get_mpz_t(), 2, exponent);
  a = a / 2;
  a = a - 1;
  a = a / exponent;

  // stage 2
  a = a - 1;
  a = a / 2;

  string digits = a.get_str();
  int sumDigits = 0;
  char d;

  for (int j = 0; j < digits.length(); j++) {
    d = digits.at(j);
    sumDigits += stoi(&d, 0, 10);
  }

  bgf.clear();
  if (a > 1) {
    bgf.find(a);
  }
  gmp_printf("<div class='box0'><h2>2<sup>%d</sup>-1</h2><br>"
             "<u>Last argument</u>:<br><p class='box1'>%Zd</p><br>"
             "<u>Factors</u>:<br><p class='box1'> %s </p><br>"
             "<u>Digits sum:</u><br>%d</div><br>"
             "<br>",
             exponent, a.get_mpz_t(), bgf.toString().c_str(), sumDigits);

  return "";
}

int main(int argc, char *argv[]) {
  argumentsHandler argHdl(argc, argv);
  primeTester pt(10);

  pt.reset();
  int action;
  int debugLevel = 0;
  int max=4;
  unsigned n = 0;

  argHdl.add(argument(0, (char *)"n", (char *)"number",
                      (char *)"Number to be factorized", (char *)"N"));
  argHdl.add(argument(1, (char *)"d", (char *)"debug", (char *)"Debug level",
                      (char *)"N"));

  while (action > -1) {
    action = argHdl.getAction();
    switch (action) {
    case 0:
      argHdl.pvalue(&max);
      //  n = argHdl.value;
      break;
    case 1:
      argHdl.pvalue(&debugLevel);
      break;
    }
  }

  printf("<html>"
         "<head>"
         "<meta http-equiv=Content-Type content=text/html; charset=iso-8859-1>"
         "<style>.box0{ border-style: solid;  border-width: 4px; padding:5px; "
         "} </style>"
         "<style>.box1{ border-style: solid;  border-width: 1px; padding:5px;  "
         "overflow-wrap: break-word; } </style>"
         "</head>"
         "<body>");

  for (int i = 0; i < max; i++) {
    n = pt.next(n);
    tirado3(n);
  }
  printf("</body></html>");
}