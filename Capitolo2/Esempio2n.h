#include <iostream>

void stampa(const int &numero)
{
    std::cout << "Il numero è: " << numero << std::endl;
    // Se si tentasse di modificare il valore di numero causerebbe un errore di compilazione
}

int main() {
    int valore = 5;
    stampa(valore);  // Passa per riferimento, ma non può essere modificato
    return 0;
}
