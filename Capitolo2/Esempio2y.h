#include <iostream>
#include <thread>
#include <chrono>

int main() {
    int bpm;
    std::cout << "Inserisci il BPM: ";
    std::cin >> bpm;

    // Calcola il numero di battiti in 10 secondi
    double battiti_per_secondo = bpm / 60.0;
    int totale_battiti = (int)(battiti_per_secondo * 10);

    std::cout << "Inizio della canzone..." << std::endl;

    for (int i = 1; i <= totale_battiti; ++i) {
        std::cout << "Battito " << i << std::endl;
        // Simula il ritardo tra i battiti
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(60000.0 / bpm)));
    }

    std::cout << "Fine della canzone." << std::endl;

    return 0;
}
