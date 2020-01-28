#include "factorizer.h"

/** 
 * Euclidean division factorizer
 * */



factorizer::factorizer(primeGenerator* primeGenerator)
{
	this->pg = primeGenerator;
	this->reset();
}

void factorizer::reset()
{
	this->factors.clear();
	this->factorsObj.clear();
}

void factorizer::find(int64 number)
{
	int64 h, former;
	former = 0;

	/*
	//Si los números en el vector es menor que la raiz cuadrada del
	//número a buscar entonces cargamos hasta que tengamos suficientes.
	if (pg->last() < sqrt(number))
	{
		pg->load(sqrt(number) + 3);
		kdebug(concatchar((char *)"Last prime loaded is: ", (char *)to_string(pg->last()).c_str()), 0, debugLevel);
	}
	*/

	//Reseteamos el generador de números primos para empezar desde 2
	pg->reset();

	//Tomamos el primer número primo (2)
	h = pg->next();

	while (true)
	{
		//Si el número es divisible por h entonces es un factor
		while (number % h == 0)
		{
			//Guardamos el factor
			factors.push_back(h);
			//dividimos es número por el primo
			number /= h;
			//Si del resultado de la división quedamos en 1, salimos.
			if (number == 1)
				return;
		}

		//Tomamos el siguiente número primo.
		h = pg->next();

		//Evaluamos qué pasa cuando llegamos al último número de la lista
		if (h == 0)
		{
			//Si el número es menor que algùn primo contenido en la tabla reseteamos
			if (pg->last() > number)
			{
				pg->reset();
				h = pg->next();

				//Chequear si el número ya fue revisado antes... para evitar ciclos infinitos
				if (number == former)
				{
					kdebug(concatchar((char*)"Infinite loop with:", p1000(former)), 0, 0);
					return;
				}
				former = number;
			}
			else
			{
				//Si el número disponible en la tabla es mayor que el que estamos buscando
				//Cerramos el proceso.
				//Enviamos un error:
				char* m = concatchar((char*)"This number is greater than my database... Sorry", p1000(number));
				kdebug(m, 1, debugLevel);
				factors.push_back(number);
				return;
			}
		}

		//Si en vez de un número primo h==0 quiere decir que llegamos
		//Al final de los números primos cargados
		//Entonces pasamos ese número como factor... pero puede que no sea primo
		//Cuidado...

		/*
		if (h == 0)
		{
			//Si el último número primo cargado es menor que el factor actual
			if (pg->last() < number)
			{
				//cargamos hasta el factor + 3..
				//pg->load(number + 3);
				kdebug(concatchar((char *)"Last prime loaded is: ", (char *)to_string(pg->last()).c_str()), 0, debugLevel);

				//Tomamos el siguiente primo
				h = pg->next();
				//Si vuelve a ser == 0 quiere decir que no hay más
				//Numeros en el archivo.
				if (h == 0)
				{
					factors.push_back(number);
					return;
				}
			}
		}
		*/
	}

	return;
}

bool factorizer::comparefactorObj(factorObject x, factorObject y)
{
	return x.base < y.base;
}

string factorizer::toString()
{
	string result = "";

	int64 base = 0;
	int64 i, j;
	factorObject* obj;
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

		//Revisar si el número sobrepasa la tabla de números primos
		if (obj->base > this->pg->last())
		{
			result += "?";
		}

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
