#include "maths_prime.h"

//Jacobi symbol
int jacobi(int a, int n)
{
    int t = 1;
    int r;
    int tmp;
    while (a != 0)
    {
        a /= 2;
        r = n % 8;
        if (r == 3 || r == 5)
        {
            t = -t;
        }
        tmp = a;
        a = n;
        n = tmp;
        if ((a % 4 == 3) && (n % 4 == 3))
        {
            t = -t;
        }
        a %= n;
        if (n == 1)
        {
            return t;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

/**
 * Test for operator performance
 * */
void operatorTest()
{

    int k = 1000000000;
    int i;
    int a = 123456789;
    int b = 234567890;
    int c;

    clock_t t1, t2;
    double tt;

    // +
    t1 = clock();
    for (i = 0; i < k; i++)
    {
        c = a + b;
    }
    t2 = clock();
    tt = (double)(t2 - t1) / (double)CLOCKS_PER_SEC;
    cout << "operator +: " << tt << endl;

    // -
    t1 = clock();
    for (i = 0; i < k; i++)
    {
        c = a - b;
    }
    t2 = clock();
    tt = (double)(t2 - t1) / (double)CLOCKS_PER_SEC;
    cout << "operator -: " << tt << endl;

    // *
    t1 = clock();
    for (i = 0; i < k; i++)
    {
        c = a * b;
    }
    t2 = clock();
    tt = (double)(t2 - t1) / CLOCKS_PER_SEC;
    cout << "operator *: " << tt << endl;

    // /
    t1 = clock();
    for (i = 0; i < k; i++)
    {
        c = a / b;
    }
    t2 = clock();
    tt = (double)(t2 - t1) / CLOCKS_PER_SEC;
    cout << "operator /: " << tt << endl;

    // %
    t1 = clock();
    for (i = 0; i < k; i++)
    {
        c = a % b;
    }
    t2 = clock();
    tt = (double)(t2 - t1) / CLOCKS_PER_SEC;
    cout << "operator %: " << tt << endl;

    // sqrt
    t1 = clock();
    for (i = 0; i < k; i++)
    {
        c = sqrt(a);
    }
    t2 = clock();
    tt = (double)(t2 - t1) / CLOCKS_PER_SEC;
    cout << "operator sqrt: " << tt << endl;

    // ==
    t1 = clock();
    for (i = 0; i < k; i++)
    {
        if (a == b)
        {
        }
    }
    t2 = clock();
    tt = (double)(t2 - t1) / CLOCKS_PER_SEC;
    cout << "operator == : " << tt << endl;

    // >
    t1 = clock();
    for (i = 0; i < k; i++)
    {
        if (a > b)
        {
        }
    }
    t2 = clock();
    tt = (double)(t2 - t1) / CLOCKS_PER_SEC;
    cout << "operator > : " << tt << endl;

    // &
    t1 = clock();
    for (i = 0; i < k; i++)
    {
        c = a & b;
    }
    t2 = clock();
    tt = (double)(t2 - t1) / CLOCKS_PER_SEC;
    cout << "operator & : " << tt << endl;

    // << 1
    t1 = clock();
    for (i = 0; i < k; i++)
    {
        c = a << 1;
    }
    t2 = clock();
    tt = (double)(t2 - t1) / CLOCKS_PER_SEC;
    cout << "operator << 1 : " << tt << endl;
}


bool isOdd(int n){
    return (n&1)==1;
}