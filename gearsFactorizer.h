#ifndef GEARS_FACTORIZER_H
#include "kdutils.h"
#include "factorObject.h"
#include "argumentsHandler.h"

class gearsFactorizer
{
public:
    void find(int64 n);
    vector<int64>factors;
    string toString();
    int debugLevel = 0;

private:
    vector<factorObject> factorsObj;
    static bool comparefactorObj(factorObject x, factorObject y);
};

 