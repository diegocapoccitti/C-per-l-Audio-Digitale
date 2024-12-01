#include <iostream>

int main() {
    float numeroVirgola;
    char lettera;
    std::string nome;
    
    std::cout << "Inserisci un numero decimale: ";
    std::cin >> numeroVirgola;
    
    std::cout << "Inserisci una lettera: ";
    std::cin >> lettera;
    
    std::cout << "Inserisci il tuo nome: ";
    std::cin >> nome;
    
    std::cout << "Hai inserito il numero: " << numeroVirgola << ", la lettera: " << lettera << " e il nome: " << nome << std::endl;
    return 0;
}
