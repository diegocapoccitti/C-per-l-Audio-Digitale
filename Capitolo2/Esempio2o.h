#include <iostream>

void incrementa(int *numero)
{
    (*numero)++;  // Modifica l'originale usando il puntatore
}

int main() {
    int valore = 5;
    incrementa(&valore);  // Passa l'indirizzo di valore
    std::cout << "Valore dopo incremento: " << valore << std::endl;  // Uscita: 6
    return 0;
}
