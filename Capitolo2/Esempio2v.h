#include <iostream>
#include <vector>

int main()
{
    std::vector<int> numeri = {1, 2, 3, 4, 5};

    for (auto it = numeri.begin(); it != numeri.end(); ++it) {
        std::cout << *it << " "; // Dereferenzia l'iteratore per ottenere il valore
    }
    return 0;
}
