#ifndef FACTORIZER_H
#include "kdutils.h"
#include "primeGenerator.h"
#include "factorObject.h"




/*
* Class to managing fatorizing
*/
class factorizer
{

public:
	factorizer(primeGenerator *primeGenerator);
	void find(int64 number);
	vector<int64> factors;
	void reset();
	string toString();
	int debugLevel = 0;
	char *filename;

private:
	primeGenerator *pg;
	vector<factorObject> factorsObj;
	static bool comparefactorObj(factorObject x, factorObject y);
};

#endif
#define FACTORIZER_H