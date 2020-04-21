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
    local m,n;
    m = 2 ^ p - 1;
    n = (2 * p) + 1;
    return m % n;
}