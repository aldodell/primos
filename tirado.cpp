#include "tirado.h"

/*
k=25964951 (r+1)=7 c=3323513729
k=13 (r+1)=28 c=3489660929
k=4423 (r+1)=20 c=4637851649
k=37156667 (r+1)=7 c=4756053377
k=9941 (r+1)=19 c=5211947009
k=1279 (r+1)=22 c=5364514817
k=24036583 (r+1)=8 c=6153365249
k=2203 (r+1)=22 c=9240051713
k=216091 (r+1)=16 c=14161739777
k=107 (r+1)=27 c=14361296897



k=127 (r+1)=18 c=33292289
k=44497 (r+1)=10 c=45564929
k=43112609 (r+1)=1 c=86225219
k=110503 (r+1)=10 c=113155073
k=2203 (r+1)=16 c=144375809
k=2281 (r+1)=16 c=149487617
k=5 (r+1)=25 c=167772161
k=89 (r+1)=21 c=186646529
k=3217 (r+1)=16 c=210829313
k=37156667 (r+1)=3 c=297253337
k=9689 (r+1)=15 c=317489153
k=9941 (r+1)=15 c=325746689
k=23209 (r+1)=14 c=380256257
k=7 (r+1)=26 c=469762049
k=107 (r+1)=23 c=897581057
k=521 (r+1)=21 c=1092616193
k=9689 (r+1)=17 c=1269956609
k=127 (r+1)=24 c=2130706433
k=17 (r+1)=27 c=2281701377
k=3 (r+1)=30 c=3221225473
k=25964951 (r+1)=7 c=3323513729
k=13 (r+1)=28 c=3489660929
k=4423 (r+1)=20 c=4637851649
k=37156667 (r+1)=7 c=4756053377
k=9941 (r+1)=19 c=5211947009
k=1279 (r+1)=22 c=5364514817
k=24036583 (r+1)=8 c=6153365249
k=2203 (r+1)=22 c=9240051713



*/

/* global vars*/
int debugLevel = 100;
char *filename;

/* Main table*/
primeGenerator pg;
factorizer fact(&pg);

int64 beginNumber = 2;
int64 mersenneExp[] = {3, 5, 7, 13, 17, 19, 31, 61, 89, 107, 127, 521, 607, 1279, 2203, 2281, 3217, 4253, 4423, 9689, 9941, 11213, 19937, 21701, 23209, 44497, 86243, 110503, 132049, 216091, 756839, 859433, 1257787, 1398269, 2976221, 3021377, 6972593, 13466917, 20996011, 24036583, 25964951, 30402457, 32582657, 37156667, 42643801, 43112609, 57885161};
int64 wagstaff[] = {11, 43, 683, 2731, 43691, 174763, 2796203, 715827883}; //, 2932031007403, 768614336404564651, 201487636602438195784363, 845100400152152934331135470251, 56713727820156410577229101238628035243};

/*
int64 ks[] = {
	3,
	9,
	15,
	53,
	63,
	303,
	639,
	1101,
	2211,
	43121,
	12018291};
	*/

	int64 ks[] = {
	3,
	11,
	1211};



vector<int64> Ks;

void getK()
{
	Ks.clear();
	int i;
	int64 k, k1, k2, f, u, v, w;
	for (i = 3; i < 257; i += 2)
	{

		//get k
		k = i;
		/*

		//Detect if k is a Wagstaff number. In this case jump it.
		if (std::find(std::begin(wagstaff), std::end(wagstaff), k) != std::end(wagstaff))
		{
			goto nextK;
		}

*/

		//Put it on form 2^k+1
		k1 = pow(2, k) + 1;

		//Put it on form 2^k-1
		k2 = pow(2, k) - 1;

	stage1:

		//Factorize k1
		fact.reset();
		fact.find(k1);

		//If not factor are form 4k+3 jump to form 4k+1
		for (u = 0; u < fact.factors.size(); u++)
		{
			f = fact.factors[u];
			v = (f - 3) / 4;
			w = (4 * v + 3);
			if (f != w)
				goto stage2;
		}
		goto stage3;

	stage2:
		//If not factor are form 4k+1 jump to other k
		for (u = 0; u < fact.factors.size(); u++)
		{
			f = fact.factors[u];
			v = (f - 1) / 4;
			w = (4 * v + 1);
			if (f != w)
				goto nextK;
		}

	stage3:

		//Factorize k2
		fact.reset();
		fact.find(k2);

		//If not factor are form 4k+3 jump to other 4k+1
		for (u = 0; u < fact.factors.size(); u++)
		{
			f = fact.factors[u];
			v = (f - 3) / 4;
			w = (4 * v + 3);
			if (f != w)
				goto stage4;
		}
		goto stage5;

	stage4:
		//If not factor are form 4k+1 jump to other k
		for (u = 0; u < fact.factors.size(); u++)
		{
			f = fact.factors[u];
			v = (f - 1) / 4;
			w = (4 * v + 1);
			if (f != w)
				goto nextK;
		}

	stage5:
		//

		Ks.push_back(k);
		cout << k << endl;

	nextK:
		//
		// Nothing to do
		k = k;
	}
}

void calculate()
{
	/*
	3489660929 13 27
	*/

	//380256257 23209 14
	//380256257 23209 14
	//	897581057 107 23
	//	1092616193 521 21

	int64 k, c, i, j, k1, k2, f;
	double long log2 = log(2);
	double long r, m;
	int u, v, w;

	//c = pg.next(3321928092);
	//332192807

	pg.load();
	pg.reset();
	beginNumber = 3;
	c = pg.next(beginNumber);
	i = 0;
	//getK();

	while (true)
	{ // k=639 (r+1)=1 c=1279
		for (j = 0; j < 3; j++)
		{
			//Get  k by it index (j) from k array.
			k = ks[j];
			//Calculate: log(C-1)-log(k)/log(2)
			r = (log(c - 1) - log(k)) / log2;
			//Rounding r
			r = round(r);
			//calculate: (2*(2^(r-1))*k) + 1
			m = (2 * (pow(2, (r - 1)) * k)) + 1;
			// if m == c then show values k,r+1,c
			if (m == c)
			{
				cout << "k=" << k << " (r+1)=" << r << " c=" << c << endl;
			}
		}

		c = pg.next();

		if (c - i > 1000000000)
		{
			cout << "--- " << c << " ---" << endl;
			i = c;
		}
		if (c == 0)
			break;
	}
}

int main(int argc, char *argv[])
{
	//file name with prime numbers
	char primeFilename[32];

	argumentsHandler argHdl(argc, argv);

	argHdl.add(argument(0, (char *)"f", (char *)"file", (char *)"Prime number file", (char *)"n"));
	argHdl.add(argument(1, (char *)"b", (char *)"begin", (char *)"First prime number to evaluate", (char *)"n"));

	int action = 0;
	while (action > -1)
	{
		action = argHdl.getAction();
		switch (action)
		{
		case 0:
			argHdl.pvalue(primeFilename, sizeof(primeFilename));
			pg.filename = primeFilename;
			break;

		case 1:
			argHdl.pvalue(&beginNumber);

		default:
			break;
		}
	}

	calculate();

	return EXIT_SUCCESS;
}

/*
Buenos dias Aldo....He decidido Cambiar la estrategia pq  con la k actual se desemboca en una  contradicion muy sutil...pero contradicion al fin....nuestra  nueva puede ser primo o compuesto...pero nunca puede ser un exponente q de un primo de Wagstaff...puede ser un exponente de los Mn o no serlo ...y ademas puede ser un impar q no sea primo...lo importante ahora es que los divisores primos de 2^k+1 y 2^k -1 sean de igual forma.   Por ejemplo los divisores de 2^15+1 son todos de la forma 4n+3 y tambien los primos divisores de 2^15 -1...entonces con k=15 hay q buscar unos C q sea primo y q den mas de  10 ^8 y 10^9 digitos...creo  q con  k=27 tambien....hay q probar primero la k de tal manera q cumpla lo dicho para 2^k+1 y 2^k -1 y despues buscar los respectivos C's....
La contradiccion surge  cuando se admite q el factor primo 3 q siempre aparece como divisor de 2^2^Rk+1....no tiene incidencia sobre si Mn resulta ser primo o no....por muy sutil el asunto no habia caido en cuenta .....seguimos batallando

 Ahora con una k mas amplia puede q el panorama para conseguir las C's sea mas amplio Taliban
 Tambien...no Taliban
[3:27 p. m., 9/12/2019] Eleazar Tirado Padre: k= 3,5,7,13,17,19,31,61,127.....etc....estan proscritas...asi con todos los exponentes q dan los primos de Wagstaff
[3:28 p. m., 9/12/2019] Eleazar Tirado Padre: Los k=89 y 107 no resultan
[3:31 p. m., 9/12/2019] Eleazar Tirado Padre: Vamos a ver como resulta k=521....me huele a q no resulte tampoco
[8:03 p. m., 9/12/2019] Eleazar Tirado Padre: Te repito q no importa los valores q tome R ...lo q importa es que k cumpla con lo establecido para 2^k+1 y 2^k -1

*/