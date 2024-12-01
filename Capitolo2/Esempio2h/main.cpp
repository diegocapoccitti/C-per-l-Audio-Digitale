#include <iostream>
#include "somma.h"

int main()
{
    int x = 5;
    int y = 10;

    int risultato = somma(x, y);

    std::cout << "La somma di " << x << " e " << y << " è: " << risultato << std::endl;

    return 0;
}
