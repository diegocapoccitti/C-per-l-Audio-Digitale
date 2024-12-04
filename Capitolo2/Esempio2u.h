#include <iostream>

int main() {
    // Array di frequenze per le note C, D, E, F, G, A, B, C
    double frequenze[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};

    // Stampa delle frequenze
    for (int i = 0; i < 8; ++i) {
        std::cout << "Frequenza della nota " << i+1 << " è: " << frequenze[i] << " Hz." << std::endl;
    }

    return 0;
}
