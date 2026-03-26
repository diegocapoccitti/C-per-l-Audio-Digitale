#include <iostream>

void incrementa(int &numero)
{
    numero++;  // Modifica l'originale
}

int main()
{
    int valore = 5;
    incrementa(valore);
    std::cout << "Valore dopo incrementa: " << valore << std::endl;  // Uscita: 6
    return 0;
}
