#include <iostream>

int main() {
    int bpm;
    std::cout << "Inserisci i BPM: ";
    std::cin >> bpm;

    double durata_quarto_nota = 60000.0 / bpm;
    std::cout << "La durata di un quarto di nota è: " << durata_quarto_nota << " ms." << std::endl;

    return 0;
}
