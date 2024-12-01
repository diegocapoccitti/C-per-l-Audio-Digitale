#include <iostream>

void incrementa(int numero)
{
    numero = numero +1;  // Modifica la copia, non l’originale!!
}

int main() {
    int valore = 5;
    incrementa(valore);
    std::cout << "Valore dopo incremento: " << valore << std::endl;  // Uscita: 5
    return 0;
}
