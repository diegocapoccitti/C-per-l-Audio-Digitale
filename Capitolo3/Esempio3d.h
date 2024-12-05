#include <iostream>

class Chitarra {
private:
    std::string modello;
    std::string tipo; // Acustica, Elettrica, Classica, ecc.
    int numeroDiCord;

public:
    // Costruttore di default
    Chitarra() {
        modello = "Modello sconosciuto";
        tipo = "Tipo sconosciuto";
        numeroDiCord = 6; // Valore predefinito per le chitarre standard
    }

    // Costruttore parametrizzato
    Chitarra(std::string m, std::string t, int cord) {
        modello = m;
        tipo = t;
        numeroDiCord = cord;
    }

    // Un altro costruttore parametrizzato per chitarre acustiche
    Chitarra(std::string m, int cord) {
        modello = m;
        tipo = "Acustica"; // Imposta il tipo come acustica
        numeroDiCord = cord;
    }

    // Metodo per visualizzare le informazioni sulla chitarra
    void mostraInfo() {
        std::cout << "Modello: " << modello
                  << ", Tipo: " << tipo
                  << ", Numero di corde: " << numeroDiCord << std::endl;
    }
};

int main()
{
    Chitarra chitarra1;  // Usa il costruttore di default
    Chitarra chitarra2("Fender Stratocaster", "Elettrica", 6); // Usa il costruttore parametrizzato
    Chitarra chitarra3("Yamaha F310", 6); // Usa il costruttore per chitarre acustiche

    chitarra1.mostraInfo(); // Modello: Modello sconosciuto, Tipo: Tipo sconosciuto, Numero di corde: 6
    chitarra2.mostraInfo(); // Modello: Fender Stratocaster, Tipo: Elettrica, Numero di corde: 6
    chitarra3.mostraInfo(); // Modello: Yamaha F310, Tipo: Acustica, Numero di corde: 6
}
