#include "primeGenerator.h"


/**
 * First version program wich build prime data base
 * */


primeGenerator::primeGenerator()
{
	this->index = 0;
	this->_last = 0;
}

void primeGenerator::generate(int64 max)
{
	this->maximum = max;

	/*
	Size memory: (2/5) * max... then /8 (to bits)
	For each number to evaluate, only save wich are finishes on ...1 ..3, ...7, ..9
	That means that for each 10 number we save only 4.
	Then each of these number are store as 1 bit.
	So we can split into 8 parts.
	Then (2/5) * (1/8) = 2/40 = 1/20
	*/
	primes.resize(max / 20);

	int64 i, j, k, l;
	i = 0;
	j = 0;
	l = 0;

	int64 SQR = sqrt(max) + 3;
	size_t t1, t2;
	AuxGenerator ag1, ag2;

	t1 = clock();

	ag1.last = 1;
	ag1.ten = 0;

	while (i < SQR)
	{
		i = ag1.next();
		if (isPrimeOpt(i))
		{
			j = 0;
			ag2.last = ag1.last - 1;
			ag2.ten = ag1.ten;
			while (j < max)
			{
				j = ag2.next();
				k = i * j;
				if (k > max)
					break;
				markNotPrime(k);
			}
		}

		cout << "*" << flush;
	}

	t2 = clock();
	cout << (double)(t2 - t1) / CLOCKS_PER_SEC << " s" << endl;
}

int64 primeGenerator::last()
{
	int i = 7;
	int64 k = 0;
	int64 block = this->primes.size() - 1ull;
	while (k == 0)
	{
		if (i < 0)
		{
			i = 7;
			block--;
		}

		k = buildPrime(block, i);
		i--;
	}
	return k;
}

void primeGenerator::load()
{
	this->load(this->filename);
}

void primeGenerator::load(char *_filename)
{
	this->filename = _filename;

	kdebug((char *)"Loading table...", 1, debugLevel);
	ifstream ifs;
	ifs.open(this->filename, ios_base::binary);

	// open the file:
	std::streampos fileSize;

	// get its size:
	ifs.seekg(0, std::ios::end);
	fileSize = ifs.tellg();
	ifs.seekg(0, std::ios::beg);

	this->primes.resize(fileSize, 0);
	ifs.read((char *)&this->primes[0], fileSize);

	ifs.close();

	string message = "... Table loaded.";
	kdebug((char *)message.c_str(), 1, debugLevel);
}

void primeGenerator::save(char *filename)
{
	kdebug((char *)"Saving table...", 1, debugLevel);
	ofstream ofs(filename, ios_base::binary);
	ofs.write((char *)&this->primes[0], this->primes.size());
	ofs.flush();
	ofs.close();
	kdebug((char *)"... table saved.", 1, debugLevel);
}

inline void primeGenerator::markNotPrime(int64 n)
{
	int64 block, mark;
	order(n, block, mark);
	primes.at(block) |= (1 << mark);
}

/**
 * Warning: this is a optimized function for internal process only
 * Even numbers and mod 5 are passed as primes numbers...
 * */
inline bool primeGenerator::isPrimeOpt(int64 n)
{
	if (n == 3 || n == 5 || n == 7)
		return true;
	int64 block, mark;
	order(n, block, mark);
	return !(primes.at(block) & (1 << mark));
}

bool primeGenerator::isPrime(int64 n)
{
	if (n == 2 || n == 3 || n == 5 || n == 7)
		return true;

	if (!(n & 1))
		return false;

	if (n % 5 == 0)
		return false;

	return isPrimeOpt(n);
}

inline int64 primeGenerator::buildPrime(int64 block, int64 offset)
{
	int64 firsts[] = {2,
					  3,
					  5,
					  7,
					  11,
					  13,
					  17,
					  19};
	if (block == 0)
	{
		return firsts[offset];
	}

	int64 terms[] = {1,
					 3,
					 7,
					 9,
					 11,
					 13,
					 17,
					 19};

	int64 i = this->primes[block];
	int64 n = 0;
	if (!(i & (1 << offset)))
	{
		n = (20ull * block) + terms[offset];
	}

	return n;
}

//Return a block and mark for calculate
inline void primeGenerator::order(int64 n, int64 &block, int64 &mark)
{
	block = (n - 1) / 20;
	int64 offset = n - (20 * block);

	switch (offset)
	{
	case 1:
		mark = 0;
		break;

	case 3:
		mark = 1;
		break;

	case 7:
		mark = 2;
		break;

	case 9:
		mark = 3;
		break;

	case 11:
		mark = 4;
		break;

	case 13:
		mark = 5;
		break;

	case 17:
		mark = 6;
		break;

	case 19:
		mark = 7;
		break;

	default:
		break;
	}
}

int64 primeGenerator::next()
{
	return this->move(1);
}

int64 primeGenerator::prev()
{
	return this->move(-1);
}

int64 primeGenerator::move(int step)
{

	//Si llegamos al final del archivo devolvemos cero
	if (this->index == (int64)(20ull * this->primes.size()))
	{
		return 0;
	}

	//Evaluamos los primeros números... No están en el archivo.
	int64 first[] = {2, 3, 5, 7};
	if (index < 4)
	{
		this->index += step;
		return first[this->index - step];
	}

	//Calculamos el bloque y el offset
	int64 block = index / 8;
	int64 offset = index - (8 * block);

	//Si llegamos al final retornamos cero
	if (block == this->primes.size())
		return 0;

	//Aunmentamos el contador
	this->index += step;

	int64 n = buildPrime(block, offset);
	if (n == 0)
		return next();

	return n;
}

int64 primeGenerator::next(int64 greaterThan)
{
	int64 k, j;
	reset();
	order(greaterThan, k, j);
	this->index = k * 8ull;
	return next();
}

void primeGenerator::list(int64 begin, int64 end)
{

	int64 p = next(begin);
	while (p < end)
	{
		cout << p1000(p) << endl;
		p = next();
	}
}

void primeGenerator::reset()
{

	this->index = 0;
}

int64 AuxGenerator::next()
{
	if (last > 3)
	{
		last = 0;
		ten++;
	}

	last++;
	return (int64)((10ull * ten) + (int64)elements[last - 1]);
}

void AuxGenerator::reset()
{
	last = 1;
	ten = 0;
}