#ifndef PRIME_GENERATOR_H
#include "kdutils.h"

class primeGenerator
{
public:
	primeGenerator();
	vector<unsigned char> primes;
	void generate(int64 max);
	int64 last();
	void save(char *filename);
	void load(char *filename);
	void load();
	void list(int64 begin, int64 end);
	inline int64 buildPrime(int64 block, int64 offset);

	bool isPrime(int64 n);
	void reset();
	int64 next();
	int64 next(int64 greaterThan);
	int64 prev();
	int64 move(int step);
	int debugLevel = 0;
	char *filename;

private:
	int64 index;
	int64 maximum;
	int64 _last;
	inline void markNotPrime(int64 n);
	inline bool isPrimeOpt(int64 n);
	inline void order(int64 n, int64 &block, int64 &mark);
};

class AuxGenerator
{
public:
	int64 next();
	void reset();
	int last;
	int64 ten = 0;
	int elements[4] = {1, 3, 7, 9};
};

#define PRIME_GENERATOR_H
#endif
