#include <iostream>

class MyClass {
public:
    int x;

    MyClass(int x) {
        this->x = x; // Usa 'this' per distinguere il membro x dalla variabile locale
    }

    void printX() {
        std::cout << "x = " << this->x << std::endl; // Si può omettere 'this', ma è esplicitamente corretto
    }
};

int main() {
    MyClass obj(5);
    obj.printX(); // Stampa x = 5
    return 0;
}
