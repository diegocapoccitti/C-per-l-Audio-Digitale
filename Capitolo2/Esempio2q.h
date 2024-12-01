#include <iostream>
#include <string>

int main()
{
    std::string nota;
    std::cout << "Inserisci una nota musicale (A, B, C, D, E, F, G): ";
    std::cin >> nota;

    if (nota == "C") {
        std::cout << "La nota " << nota << " corrisponde a do." << std::endl;
    } else if (nota == "D") {
        std::cout << "La nota " << nota << " corrisponde a re." << std::endl;
    } else if (nota == "E") {
        std::cout << "La nota " << nota << " corrisponde a mi." << std::endl;
    } else if (nota == "F") {
        std::cout << "La nota " << nota << " corrisponde a fa." << std::endl;
    } else if (nota == "G") {
        std::cout << "La nota " << nota << " corrisponde a sol." << std::endl;
    } else if (nota == "A") {
        std::cout << "La nota " << nota << " corrisponde a la." << std::endl;
    } else if (nota == "B") {
        std::cout << "La nota " << nota << " corrisponde a si." << std::endl;
    } else {
        std::cout << "Nota non riconosciuta." << std::endl;
    }

    return 0;
}
