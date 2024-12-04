#include <iostream>
#include <string>

int main() {
    std::string comando = "";

    while (comando != "stop") {
        std::cout << "Inserisci comando (play/stop): ";
        std::cin >> comando;

        if (comando == "play") {
            std::cout << "Riproduzione in corso..." << std::endl;
            // Codice per avviare la riproduzione
        } else if (comando == "stop") {
            std::cout << "Riproduzione terminata." << std::endl;
        } else {
            std::cout << "Comando non riconosciuto." << std::endl;
        }
    }

    return 0;
}
