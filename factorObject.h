#ifndef FACTOR_OBJECT_H
#include "kdutils.h"

/** classes */
class factorObject
{
public:
	int64 base;
	int exp;
	bool used;
	factorObject()
	{
		base = 0;
		exp = 0;
		used = false;
	};
	factorObject(int64 base, int exp)
	{
		this->base = base;
		this->exp = exp;
	};
};

#define FACTOR_OBJECT_H
#endif