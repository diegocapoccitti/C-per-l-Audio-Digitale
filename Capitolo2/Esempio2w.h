#include <iostream>
#include <map>
#include <cmath>
#include <string>

// Funzione per ottenere la frequenza di base di una nota
double getFrequenzaBase(const std::string &nota) {
    std::map<std::string, double> mappa_frequenze = {
        {"C", 261.63},
        {"D", 293.66},
        {"E", 329.63},
        {"F", 349.23},
        {"G", 392.00},
        {"A", 440.00},
        {"B", 493.88}
    };

    if (mappa_frequenze.find(nota) != mappa_frequenze.end()) {
        return mappa_frequenze[nota];
    } else {
        return -1.0; // Indica una nota non valida
    }
}

// Funzione per calcolare la frequenza con le ottave
double calcolaFrequenzaOttave(double base, int ottave) {
    return base * pow(2.0, ottave);
}

int main() {
    std::string nota;
    int ottave;

    std::cout << "Inserisci la nota di base (C, D, E, F, G, A, B): ";
    std::cin >> nota;

    double frequenza_base = getFrequenzaBase(nota);
    if (frequenza_base == -1.0) {
        std::cout << "Nota non valida." << std::endl;
        return 1;
    }

    std::cout << "Inserisci il numero di ottave: ";
    std::cin >> ottave;

    double frequenza_finale = calcolaFrequenzaOttave(frequenza_base, ottave);
    std::cout << "La frequenza della nota " << nota << " dopo " << ottave << " ottave è: " << frequenza_finale << " Hz." << std::endl;

    return 0;
}
