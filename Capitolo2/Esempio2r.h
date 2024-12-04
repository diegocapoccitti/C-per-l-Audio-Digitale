#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> sequenza = {"C", "D", "E", "F", "G", "A", "B", "C"};

    for (int i = 0; i < sequenza.size(); ++i) {
        std::cout << "Nota " << i+1 << ": " << sequenza[i] << std::endl;
        // Qui si potrebbe aggiungere il codice per riprodurre la nota
    }

    return 0;
}
