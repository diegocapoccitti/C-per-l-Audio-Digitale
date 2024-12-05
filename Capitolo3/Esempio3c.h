#include <iostream>

enum Nota { Do, Re, Mi, Fa, Sol, La, Si };

void suonaNota(Nota nota) {
    switch (nota) {
        case Do:
            std::cout << "Suona il Do" << std::endl;
            break;
        case Re:
            std::cout << "Suona il Re" << std::endl;
            break;
        case Mi:
            std::cout << "Suona il Mi" << std::endl;
            break;
        default:
            std::cout << "Nota non riconosciuta" << std::endl;
    }
}

int main()
{
    Nota miaNota = Re;
    suonaNota(miaNota); // Stampa: Suona il Re
    return 0;
}
