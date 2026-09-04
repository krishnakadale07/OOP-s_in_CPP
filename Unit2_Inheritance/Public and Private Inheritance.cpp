#include <iostream>

class Base {
public:
    void show() const {
        std::cout << "Base public function\n";
    }
};

class PublicDerived : public Base {
};

class PrivateDerived : private Base {
public:
    void callBaseShow() const {
        show();
    }
};

int main() {
    PublicDerived publicObject;
    publicObject.show();

    PrivateDerived privateObject;
    privateObject.callBaseShow();

    return 0;
}