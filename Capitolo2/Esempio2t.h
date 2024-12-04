#include <iostream>
#include <string>

int main() {
    std::string opzione;

    do {
        std::cout << "\nMenu Opzioni:\n";
        std::cout << "1. Riproduci Musica\n";
        std::cout << "2. Interrompi Musica\n";
        std::cout << "3. Esci\n";
        std::cout << "Scegli un'opzione: ";
        std::cin >> opzione;

        if (opzione == "1") {
            std::cout << "Musica in riproduzione..." << std::endl;
            // Codice per riprodurre musica
        } else if (opzione == "2") {
            std::cout << "Musica interrotta." << std::endl;
            // Codice per interrompere musica
        } else if (opzione == "3") {
            std::cout << "Uscita dal programma." << std::endl;
        } else {
            std::cout << "Opzione non valida. Riprova." << std::endl;
        }

    } while (opzione != "3");

    return 0;
}
