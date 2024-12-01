#include <memory> // Necessario per std::unique_ptr e std::make_unique
#include <iostream>

int main() {
    // Dichiarazione e inizializzazione di un unique_ptr con make_unique
    std::unique_ptr<int> ptr = std::make_unique<int>(42);

    // Accesso al valore gestito dall'unique_ptr
    std::cout << "Il valore è: " << *ptr << std::endl;

    return 0;
}
