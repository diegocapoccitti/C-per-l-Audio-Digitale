#include <iostream>
#include <string>

// Classe base
class StrumentoMusicale {
public:
    std::string nome;
    
    StrumentoMusicale(std::string n) : nome(n) {}

    void suona() {
        std::cout << "Sto suonando " << nome << "." << std::endl;
    }
};

// Classe derivata
class Pianoforte : public StrumentoMusicale {
public:
    int numeroTasti;

    Pianoforte(std::string n, int tasti) : StrumentoMusicale(n), numeroTasti(tasti) {}

    void suona() {
        std::cout << "Sto suonando il pianoforte " << nome << " con " << numeroTasti << " tasti." << std::endl;
    }
};

// Classe derivata
class Chitarra : public StrumentoMusicale {
public:
    int numeroCorde;

    Chitarra(std::string n, int corde) : StrumentoMusicale(n), numeroCorde(corde) {}

    void suona() {
        std::cout << "Sto suonando la chitarra " << nome << " con " << numeroCorde << " corde." << std::endl;
    }
};

int main() {
    // Creiamo un oggetto della classe Pianoforte
    Pianoforte piano("Yamaha", 88);
    
    // Creiamo un oggetto della classe Chitarra
    Chitarra chitarra("Fender", 6);
    
    // Chiamiamo il metodo suona() per il pianoforte
    piano.suona();
    
    // Chiamiamo il metodo suona() per la chitarra
    chitarra.suona();

    return 0;
}
