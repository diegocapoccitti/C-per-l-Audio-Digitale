#include <iostream>

class StrumentoMusicale
{
public:
    // Attributi pubblici
    std::string nome;
    int numeroTasti;

    // Costruttore
    StrumentoMusicale(std::string n, int t) {
        nome = n;
        numeroTasti = t;
    }

    // Metodo pubblico
    void suona() {
        std::cout << "Sto suonando " << nome << " con " << numeroTasti << " tasti." << std::endl;
    }

private:
    // Attributo privato
    bool accordato;

    // Metodo privato
    void accorda() {
        accordato = true;
    }
};

int main()
{
    StrumentoMusicale pianoforte("Pianoforte", 88);
    StrumentoMusicale chitarra("Chitarra", 6);
    
    pianoforte.suona(); // Output: Sto suonando Pianoforte con 88 tasti.
    chitarra.suona();  // Output: Sto suonando Chitarra con 6 tasti
    
    std::cout << "Il " << pianoforte.nome << " ha " << pianoforte.numeroTasti << " tasti." << std::endl;
    std::cout << "La " << chitarra.nome << " ha " << chitarra.numeroTasti << " tasti." << std::endl;
}
