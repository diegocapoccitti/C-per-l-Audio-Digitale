#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    int numero_note;
    std::cout << "Quante note vuoi inserire? ";
    std::cin >> numero_note;

    std::vector<std::string> sequenza;
    std::string nota;

    for (int i = 0; i < numero_note; ++i) {
        std::cout << "Inserisci la nota " << i+1 << ": ";
        std::cin >> nota;
        sequenza.push_back(nota);
    }

    std::cout << "\nSequenza originale:\n";
    for (const auto &n : sequenza) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // Inverti la sequenza
    std::reverse(sequenza.begin(), sequenza.end());

    std::cout << "\nSequenza inversa:\n";
    for (const auto &n : sequenza) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    return 0;
}
