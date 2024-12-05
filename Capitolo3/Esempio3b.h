#include <iostream>

class MyClass {
public:
    int x;

    MyClass& setX(int x) {
        this->x = x;
        return *this; // Restituisce l'oggetto corrente per il chaining
    }

    void printX() {
        std::cout << "x = " << x << std::endl;
    }
};

int main() {
    MyClass obj;
    obj.setX(5).printX(); // Metodo chaining
    return 0;
}
