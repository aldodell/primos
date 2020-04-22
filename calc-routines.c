define oddSum(a, b)
{
    local i, j;
    for (i = a; i <= b; i += 2)
    {
        j = j + i;
    }
    return j;
}

//retorna el módulo del primer "posible factor" de un 2^p-1
define q(p)
{
    local m, n;
    m = 2 ^ p - 1;
    n = (2 * p) + 1;
    return m % n;
}

//Test básico de primaridad
define pt(p)
{

    local m, n, r, p2, b, k;
    m = 2 ^ p - 1;
    r = isqrt(m);
    p2 = 2 * p;
    n = p2 + 1;
    b = 0;
    while (b == 0)
    {
        if (ismult(m, n))
        {
            k = (n - 1) / p2;
            printf("f=%d k0=%d\n", n, k);
            b = 1;
        }
        n = n + p2;
        if (n > r)
            b = 2;
    }

    if (b == 2)
    {

        printf("Prime");
    }
}