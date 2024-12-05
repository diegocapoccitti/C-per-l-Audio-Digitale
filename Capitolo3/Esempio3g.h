#include <iostream>

// Classe base
class StrumentoMusicale
{
public:
    virtual void suona() {
        std::cout << "Sto suonando uno strumento musicale generico." << std::endl; //notare la keyword VIRTUAL
    }
};

// Classe derivata
class Pianoforte : public StrumentoMusicale
{
public:
    void suona() override //notare la keyword OVERRIDE
{
        std::cout << "Sto suonando un pianoforte." << std::endl;
    }
};

// Classe derivata
class Chitarra : public StrumentoMusicale
{
public:
    void suona() override //notare la keyword OVERRIDE
{
        std::cout << "Sto suonando una chitarra." << std::endl;
    }
};

int main() {
    // Puntatore alla classe base
    StrumentoMusicale* strumento;

    // Istanzia un oggetto di tipo Pianoforte
    Pianoforte piano;
    strumento = &piano;
    strumento->suona();  // Output: Sto suonando un pianoforte.

    // Istanzia un oggetto di tipo Chitarra
    Chitarra chitarra;
    strumento = &chitarra;
    strumento->suona();  // Output: Sto suonando una chitarra.

    return 0;
}
