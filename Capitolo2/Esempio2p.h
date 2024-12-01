#include <iostream>
#include <cmath> // Per usare pow()

// Funzione che calcola la frequenza di una nota
double calcolaFrequenza(int nota) {
    return 440.0 * pow(2.0, (nota - 49) / 12.0); // Nota 49 è A4 (440 Hz)
}

int main() {
    int nota = 49; // A4
    double frequenza = calcolaFrequenza(nota);
    std::cout << "La frequenza della nota " << nota << " è: " << frequenza << " Hz." << std::endl;
    return 0;
}
