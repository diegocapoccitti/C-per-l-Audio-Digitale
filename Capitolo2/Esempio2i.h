#include <iostream>

// Dichiarazione della funzione
int somma(int a, int b)
{
    return a + b;
}

int main() {
    int risultato = somma(5, 3); // Chiamata della funzione
    std::cout << "La somma è: " << risultato << std::endl;
    return 0;
}
