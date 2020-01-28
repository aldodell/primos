#include "kdutils.h"

char *concat(char *a, char *b) {
  char *qq = (char *)malloc((strlen(a) + strlen(b)) * sizeof(char));
  strcpy(qq, a);
  strcat(qq, b);
  return qq;
}

char *concatchar(char *c1, char *c2, char *c3, char *c4, char *c5, char *c6) {
  int l = strlen(c1) + strlen(c2);

  if (c3 != NULL) {
    l += strlen(c3);

    if (c4 != NULL) {
      l += strlen(c4);
      if (c5 != NULL) {
        l += strlen(c5);
        if (c6 != NULL) {
          l += strlen(c6);
        }
      }
    }
  }

  char *r = (char *)malloc(l * sizeof(char));
  strcpy(r, c1);
  strcat(r, c2);

  if (c3 != NULL) {
    strcat(r, c3);
    if (c4 != NULL) {
      strcat(r, c4);
      if (c5 != NULL) {
        strcat(r, c5);
        if (c6 != NULL) {
          strcat(r, c6);
        }
      }
    }
  }

  return r;
}

// Convert value (string) to charValue (char *)
char *stringToChar(string &value) {
  std::vector<char> writable(value.begin(), value.end());
  writable.push_back('\0');
  return &writable[0];
}

/** Helper for debug and verbose */
void kdebug(char *message, int levelRequired, int debugLevel) {
  if (levelRequired >= debugLevel) {
    cout << message << endl;
  }
}

char *p1000(unsigned long long value) {
  string s = to_string(value);

  int len = s.length();
  int dlen = 3;
  while (len > dlen) {

    s.insert(len - dlen, ".");
    dlen += 4;
    len += 1;
  }

  return stringToChar(s);
}

bool file_exists(const std::string &name) {
  ifstream f(name.c_str());
  return f.good();
}

void kdTimer::start() {
  this->tIni = clock();
  this->tSnap = this->tIni;
}

double kdTimer::snapshoot() {
  double t = (double)(clock() - this->tSnap) / CLOCKS_PER_SEC;
  this->tSnap = clock();
  return t;
}

double kdTimer::stop() {
  this->tEnd = clock();
  double t = (double)(this->tEnd - this->tIni) / CLOCKS_PER_SEC;
  return t;
}

kdProcessSpin::kdProcessSpin() {
  this->marks.push_back((char *)"|");
  this->marks.push_back((char *)"/");
  this->marks.push_back((char *)"-");
  this->marks.push_back((char *)"\\");
}

void kdProcessSpin::reset() { this->cycles = 0; }

void kdProcessSpin::show() {
  this->cycles++;
  if (this->cycles == this->cyclesForStep) {
    this->cycles = 0;
    cout << "\b" << this->marks[this->index];
    cout.flush();
    this->index++;
    if (this->index == this->marks.size()) {
      this->index = 0;
    }
  }
}
