#include "segmentedPrimeGenerator.h"

void segmentedPrimeGenerator::clearBuffer() {
  this->buffer.clear();
  this->buffer.resize(BLOCKS_BY_FILE, 0);
}

void segmentedPrimeGenerator::reset() { this->index = 0; }

void inline segmentedPrimeGenerator::calculatePosition(int64 number,
                                                       int &_fileIndex,
                                                       int64 &block,
                                                       int &offset) {

  int flag;
  // Block
  block = number / 20ull;

  // Get file index
  _fileIndex = block / BLOCKS_BY_FILE;

  // Get block into file (offset)
  block = block - ((int64)_fileIndex * BLOCKS_BY_FILE);

  // Get bit mask offset
  flag = number - (20 * (_fileIndex * BLOCKS_BY_FILE)) - 20 * block;

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
}

int64 inline segmentedPrimeGenerator::calculateNumber(int64 position,
                                                      int &_fileIndex,
                                                      int64 &block,
                                                      int &offset) {
  // First 10 positions are special because don't acomplishes with
  // Rules. So we return true value inmediatly
  int64 r = 0;

  if (position < 4) {
    switch (position) {
    case 0:
      r = 2;
      break;

    case 1:
      r = 3;
      break;

    case 2:
      r = 5;
      break;

    case 3:
      r = 7;
      break;
    }
    offset = position;
    block = 0;
    _fileIndex = 0;
    return r;
  }

  // Calculate block:
  block = position / 8;

  // calculate file index
  _fileIndex = block / BLOCKS_BY_FILE;

  block = block - (int64)(_fileIndex * BLOCKS_BY_FILE);

  // Calculate offset:
  offset = position - (8 * (_fileIndex * BLOCKS_BY_FILE)) - (8 * block);

  int flag = 0;

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

  r = (20 * ((_fileIndex * ((int64)_fileIndex * BLOCKS_BY_FILE)) + block)) +
      flag;
  return r;
}

int64 segmentedPrimeGenerator::nextTo(int64 number) {
  this->reset();
  int64 n;
  while (true) {
    n = this->move(1);
    if (n >= number)
      return n;
    if (n == 0)
      return 0;
  }
  return 0;
}

int64 segmentedPrimeGenerator::next() { return this->move(1); }

int64 segmentedPrimeGenerator::prev() { return this->move(-1); }

int64 segmentedPrimeGenerator::move(int step) {

  // determine coordinates to look up the number
  int _fileIndex, offset;
  int64 block;

  // Get current number
  int64 number = this->calculateNumber(this->index, _fileIndex, block, offset);

  // Check bounds
  if ((long)(this->index + step) < 0)
    return 0;
  if (number >= this->maximum)
    return 0;

  // Increment or decrement index
  this->index += step;

  if (this->fileIndex != _fileIndex) {
    this->load(_fileIndex);
    this->fileIndex = _fileIndex;
  }

  unsigned char b, c;
  b = this->buffer[block];
  c = (1 << offset);

  if ((b & c) == c) {
    return this->move(step);
  }

  return number;
}

/* Used for mark a bit wich represents a number as prime
 */
void inline segmentedPrimeGenerator::setNotPrime(vector<int64> &buffer) {

  this->mutexBuffer.lock();

  int _fileIndex, offset;
  int64 block;

  for (int64 number : buffer) {
    if (number >= 11) {

      this->calculatePosition(number, _fileIndex, block, offset);

      if (this->fileIndex != _fileIndex) {
        if (this->fileIndex == -1) {
          this->fileIndex = 0;
        }
        // this->mutexBuffer.lock();
        this->save(this->fileIndex);
        this->load(_fileIndex);
        // this->mutexBuffer.unlock();
        this->fileIndex = _fileIndex;
      }
      unsigned char b = this->buffer[block];
      b = b | (1 << offset);
      this->buffer[block] = b;
    }
  }
  this->mutexBuffer.unlock();
}

void segmentedPrimeGenerator::save(int _fileIndex) {
  string filename = this->getFileName(_fileIndex);
  ofstream ofs(filename, ios_base::binary);
  ofs.write((char *)&this->buffer[0], this->buffer.size());
  ofs.flush();
  ofs.close();
}

void segmentedPrimeGenerator::load(int _fileIndex) {
  string filename = this->getFileName(_fileIndex);
  if (file_exists(filename)) {
    int64 q = (int64)(1 + _fileIndex) * BLOCKS_BY_FILE * 20;
    if (this->maximum < q)
      this->maximum = q;
    vector<unsigned char> bf(BLOCKS_BY_FILE);
    ifstream ifs;
    ifs.open(filename, ios_base::binary);
    ifs.read((char *)&bf[0], BLOCKS_BY_FILE);
    ifs.close();
    this->buffer.swap(bf);
  }
}

string segmentedPrimeGenerator::getFileName(int fileIndex) {
  return filePrefix + to_string(fileIndex) + (char *)".bin";
}

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

bool ascendantOrder(int64 a, int64 b) { return a < b; }

void generatorAux(primePart *part, segmentedPrimeGenerator *spg) {

  vector<int64> buffer;

  int s1[] = {2, 4, 2, 2}; // separation for 1,3,7,9
  int64 a, b, p, pmax;

  // Indice de para calcular a
  int i = 0;

  // Indice para calcular b
  int j = 0;

  // producto de a x b;
  p = 0;
  a = 3;
  i = 1;
  normalized n;

  // Special case p=27
  if ((part->begin <= 27) && (part->end >= 27)) {
    buffer.push_back(27);
  }

  int q = 0;

  b = part->begin / a;
  n = normalizer(b);
  b = n.value;
  j = n.index;

  while (true) {

    while (true) {
      q++;
      p = a * b;
      if (p > part->end)
        break;
      buffer.push_back(p);
      b += s1[j];
      j++;
      if (j == 4)
        j = 0;
    }
    a += s1[i];
    i++;
    if (i == 4)
      i = 0;
    b = a;
    j = i;

    if ((a * a) > part->end)
      break;
  }

  if (spg->debugLevel > 1) {

    cout << "Segment " << part->begin << " - " << part->end << " ready to save."
         << endl;
    cout << "\tBuffer has " << buffer.size() << " numbers. ("
         << buffer.size() * sizeof(int64) << " bytes)" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  // std::sort(buffer.begin(), buffer.end());
  // buffer.erase(std::unique(buffer.begin(), buffer.end()));
  // this_thread::yield();
  spg->setNotPrime(buffer);
}

void segmentedPrimeGenerator::generate(int64 max, int64 partsCount) {
  // Save a reference to last number
  this->maximum = max;

  // Parts to split calculus
  // int64 partsCount = 16;
  primePart parts[partsCount];
  int64 partSize = max / partsCount;
  int i;
  for (i = 0; i < partsCount; i++) {
    parts[i].begin = (i * partSize) + 1;
    parts[i].end = (i * partSize) + partSize - 1;
  }

  parts[0].begin = 3;

  int pc = partsCount;
  int j = 0;
  vector<std::thread> ts;

  while (pc > 0) {
    for (int i = 0; i < 10; i++) {
      if (pc == 0)
        break;
      primePart *pp = &parts[j];
      ts.emplace_back(&generatorAux, pp, this);
      pc--;
      j++;
    }

    for (auto &t : ts) {
      t.join();
    }
    ts.clear();
  }
  this->save(this->fileIndex);
}

int main(int argc, char *argv[]) {

  // argument handler:
  argumentsHandler argHdl(argc, argv);
  int action = 0;
  int debugLevel = 0;
  int64 n, begin, end;
  int partsCount = 8;
  bool flagGenerate = false;
  bool flagFind = false;

  argHdl.add(argument(0, (char *)"n", (char *)"number",
                      (char *)"Max number to find", (char *)"N"));
  argHdl.add(argument(1, (char *)"d", (char *)"debug", (char *)"Debug level",
                      (char *)"N"));
  argHdl.add(argument(2, (char *)"g", (char *)"generate",
                      (char *)"Build primes number database", (char *)""));
  argHdl.add(argument(
      3, (char *)"f", (char *)"find",
      (char *)"Find into data base. Use begin and end arguments", (char *)""));
  argHdl.add(argument(4, (char *)"b", (char *)"begin",
                      (char *)"First number to find.", (char *)""));
  argHdl.add(argument(5, (char *)"e", (char *)"end",
                      (char *)"Last number to find", (char *)""));
  argHdl.add(argument(6, (char *)"s", (char *)"segments",
                      (char *)"How many segments to split", (char *)"N"));

  while (action > -1) {
    action = argHdl.getAction();

    switch (action) {
    case 0:
      argHdl.pvalue(&n);
      break;

    case 1:
      argHdl.pvalue(&debugLevel);
      break;

    case 2:
      // Go to generate
      flagGenerate = true;
      break;

    case 3:
      flagFind = true; // Find a number
      break;

    case 4:
      argHdl.pvalue(&begin);
      break;

    case 5:
      argHdl.pvalue(&end);
      break;

    case 6:
      argHdl.pvalue(&partsCount);
      break;
    }
  }

  segmentedPrimeGenerator spg;
  spg.debugLevel = debugLevel;

  if (flagGenerate) {
    spg.reset();
    clock_t t1, t2;
    t1 = clock();
    spg.generate(n, partsCount);
    t2 = clock();
    if (spg.debugLevel > 0) {
      cout << "Generate on " << (double)(t2 - t1) / CLOCKS_PER_SEC << "s."
           << endl;
    }
  }

  if (flagFind) {
    spg.reset();
    spg.load(0);
    n = spg.nextTo(begin);
    while (true) {
      cout << n << endl;
      n = spg.next();
      if (n == 0)
        break;
      if (n >= end)
        break;
    }
  }
  exit(0);
}