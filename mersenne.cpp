#include "mersenne.h"

/**
 * Little program used for generate Mersenne's numbers
 * */


string mersenne(int64 p)
{
    mpz_class m;
    mpz_ui_pow_ui(m.get_mpz_t(), 2, p);
    mpz_sub_ui(m.get_mpz_t(), m.get_mpz_t(), 1);
    return m.get_str();
}

int main(int argc, char *argv[])
{

    //argument handler:
    argumentsHandler argHdl(argc, argv);
    int action = 0;
    int debugLevel = 0;
    int64 n;

    argHdl.add(argument(0, (char *)"p", (char *)"number", (char *)"p in (2^p-1)", (char *)"N"));
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

    cout << mersenne(n) << endl;
    exit(0);
}
