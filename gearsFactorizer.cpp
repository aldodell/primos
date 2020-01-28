#include "gearsFactorizer.h"

void gearsFactorizer::find(int64 n)
{
	//cout << "n=" << n << endl;
	int64 a, b, c, d;
	int ciclos = 0;
	/**
     *  Dividir n por 2 cuantas veces sea posible
     * para convertir n en un número impar
     * */

	while ((n & 1) == 0)
	{
		n /= 2;
		this->factors.push_back(2);
		if (debugLevel > 0)
		{
			cout << "Found '2' factor. Now factorizing " << n << "." << endl;
		}
	}

	//Obtener raíz cuadrada de n
	a = sqrt(n);
	d = a;
	//Sí la raíz es par restamos 1 para que el engranaje sea impar
	if ((a & 1) == 0)
		a--;

	if (a == 1)
		a = 3;

	//Seteamos el segundo engranaje igual al primero
	b = a;
	//obtenemos el primer producto
	c = a * b;

	if (c == n)
	{
		this->factors.push_back(a);
		this->factors.push_back(b);
		return;
	}

	while (c != n)
	{
		ciclos++;
		if (debugLevel > 1)
			cout << "Cycle:" << ciclos << " a:" << a << " b:" << b << " a*b:" << c << " a-b:" << a - b << endl;

		//Operamos los engranajes

		if (c < n)
			a += 2;
		if (c > n)
			b -= 2;

		//Salimos cuando b es un factor trivial (1)
		if (b == 1)
		{
			if (debugLevel > 0)
			{
				cout << "Found " << n << " prime factor." << endl;
			}
			this->factors.push_back(n);
			a = n;
			c = n;
			break;
		}

		//Salimos si el producto de ambos engranajes es igual
		// a n
		c = a * b;
		if (c == n)
		{
			if (debugLevel > 0)
			{
				cout << "Found " << a << " factor. Call recursively to factorize it." << endl;
			}
			this->find(a);
			this->find(b);
			break;
		}
	}

	if (debugLevel > 1)
		cout << "----- Cycle:" << ciclos << " a:" << a << " b:" << b << " a*b:" << c << " a-b:" << a - b << endl;
	ciclos = 0;
}

string gearsFactorizer::toString()
{
	string result = "";

	int64 base = 0;
	int64 i, j;
	factorObject *obj;
	bool flag = true;

	//Se recorren todos los factores
	for (i = 0; i < this->factors.size(); i++)
	{

		flag = true;
		base = this->factors.at(i);

		//Se recorren la representación de los factores
		for (j = 0; j < this->factorsObj.size(); j++)
		{

			obj = &this->factorsObj.at(j);
			//Si existe una representación previamente guardada con la base en cuestión
			//aunmentamos sólo el exponente
			if (obj->base == base)
			{
				obj->exp++;
				flag = false;
			}
		}
		//Si no exite una representación con la base en cuestión entonces la guardamos
		if (flag)
		{
			this->factorsObj.push_back(factorObject(base, 1));
		}
	}

	//ordenamos la representación de factores
	std::sort(this->factorsObj.begin(), this->factorsObj.end(), this->comparefactorObj);

	//Creamos la cadena:
	//Recorremos nuevamente la representación de factores
	for (j = 0; j < this->factorsObj.size(); j++)
	{
		obj = &this->factorsObj.at(j);

		//Anexamos la base:
		result += p1000(obj->base);

		//Si el exponente > 1 agregamos el exponente:
		if (obj->exp > 1)
		{
			result += "^" + to_string(obj->exp);
		}

		//Si no estamo en el último factor agregamos el asterisco de los productos y espacios
		if (j < this->factorsObj.size() - 1)
		{
			result += " * ";
		}
	}
	return result;
}

bool gearsFactorizer::comparefactorObj(factorObject x, factorObject y)
{
	return x.base < y.base;
}

int main(int argc, char *argv[])
{

	//argument handler:
	argumentsHandler argHdl(argc, argv);
	gearsFactorizer gf;
	int action = 0;
	int debugLevel = 0;
	int64 n;

	argHdl.add(argument(0, (char *)"n", (char *)"number", (char *)"Number to be factorized", (char *)"N"));
	argHdl.add(argument(1, (char *)"d", (char *)"debug", (char *)"Debug level", (char *)"N"));

	while (action > -1)
	{
		action = argHdl.getAction();
		switch (action)
		{
		case 0:
			argHdl.pvalue(&n);
			break;
		case 1:
			argHdl.pvalue(&debugLevel);
			break;
		}
	}

	gf.debugLevel = debugLevel;
	gf.find(n);
	cout << gf.toString() << endl;

	return 0;
}
