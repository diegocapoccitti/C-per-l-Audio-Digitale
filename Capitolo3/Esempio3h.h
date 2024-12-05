#include <iostream>
#include <string>
#include <vector>

// Classe base EffettoAudio
class EffettoAudio {
public:
    std::string nomeEffetto;

    // Costruttore
    EffettoAudio(std::string nome) : nomeEffetto(nome) {}

    // Distruttore virtuale
    virtual ~EffettoAudio() {
        std::cout << "Effetto " << nomeEffetto << " rimosso." << std::endl;
    }

    // Metodo virtuale per applicare l'effetto
    virtual void applicaEffetto() {
        std::cout << "Sto applicando l'effetto " << nomeEffetto << "." << std::endl;
    }
};

// Classe derivata Riverbero
class Riverbero : public EffettoAudio {
public:
    int durata;

    // Costruttore che inizializza durata
    Riverbero(int d) : EffettoAudio("Riverbero"), durata(d) {}

    // Sovrascrive il metodo applicaEffetto
    void applicaEffetto() override {
        std::cout << "Sto applicando il riverbero con durata di " << durata << " secondi." << std::endl;
    }
};

// Classe derivata Delay
class Delay : public EffettoAudio {
public:
    int ritardo;

    // Costruttore che inizializza ritardo
    Delay(int r) : EffettoAudio("Delay"), ritardo(r) {}

    // Sovrascrive il metodo applicaEffetto
    void applicaEffetto() override {
        std::cout << "Sto applicando il delay con un ritardo di " << ritardo << " millisecondi." << std::endl;
    }
};

// Classe derivata Distorsione
class Distorsione : public EffettoAudio {
public:
    int intensità;

    // Costruttore che inizializza intensità
    Distorsione(int i) : EffettoAudio("Distorsione"), intensità(i) {}

    // Sovrascrive il metodo applicaEffetto
    void applicaEffetto() override {
        std::cout << "Sto applicando la distorsione con intensità " << intensità << "." << std::endl;
    }
};

// Classe base StrumentoMusicale
class StrumentoMusicale {
public:
    std::string nome;

    // Costruttore che inizializza il nome dello strumento
    StrumentoMusicale(std::string n) : nome(n) {}

    // Distruttore virtuale
    virtual ~StrumentoMusicale() {
        std::cout << "Strumento " << nome << " distrutto." << std::endl;
    }

    // Metodo virtuale per suonare lo strumento
    virtual void suona() {
        std::cout << "Sto suonando " << nome << "." << std::endl;
    }

    // Metodo per applicare un effetto allo strumento
    void applicaEffetto(EffettoAudio* effetto) {
        effetto->applicaEffetto();
    }
};

// Classe derivata Chitarra
class Chitarra : public StrumentoMusicale {
public:
    int numeroCorde;

    // Costruttore che inizializza nome e numero di corde
    Chitarra(std::string n, int corde) : StrumentoMusicale(n), numeroCorde(corde) {}

    // Sovrascrive il metodo suona
    void suona() override {
        std::cout << "Sto suonando la chitarra " << nome << " con " << numeroCorde << " corde." << std::endl;
    }
};

// Classe derivata Sintetizzatore
class Sintetizzatore : public StrumentoMusicale {
public:
    int bandeEQ;

    // Costruttore che inizializza nome e numero di bande EQ
    Sintetizzatore(std::string n, int bande) : StrumentoMusicale(n), bandeEQ(bande) {}

    // Sovrascrive il metodo suona
    void suona() override {
        std::cout << "Sto suonando il sintetizzatore " << nome << " con " << bandeEQ << " bande di equalizzazione." << std::endl;
    }
};

// Funzione per applicare effetti a più strumenti, utilizzando polimorfismo
void applicaEffettiSuStrumenti(std::vector<StrumentoMusicale*>& strumenti, EffettoAudio* effetto) {
    for (auto& strumento : strumenti) {
        strumento->suona();
        strumento->applicaEffetto(effetto);
    }
}

int main() {
    // Creazione degli effetti
    Riverbero riverbero(5); // Durata di 5 secondi
    Delay delay(300);       // Ritardo di 300 millisecondi
    Distorsione distorsione(7); // Intensità 7

    // Creazione degli strumenti
    Chitarra chitarra("Fender Stratocaster", 6); // Chitarra con 6 corde
    Sintetizzatore sintetizzatore("Moog", 3);    // Sintetizzatore con 3 bande EQ

    // Creazione di un vettore di strumenti
    std::vector<StrumentoMusicale*> strumenti = {&chitarra, &sintetizzatore};

    // Applicazione di vari effetti sui diversi strumenti
    std::cout << "\nApplico riverbero sugli strumenti:\n";
    applicaEffettiSuStrumenti(strumenti, &riverbero);

    std::cout << "\nApplico delay sugli strumenti:\n";
    applicaEffettiSuStrumenti(strumenti, &delay);

    std::cout << "\nApplico distorsione sugli strumenti:\n";
    applicaEffettiSuStrumenti(strumenti, &distorsione);

    return 0;
}
