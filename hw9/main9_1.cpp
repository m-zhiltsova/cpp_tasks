#include <iostream>
#include <string>

class generic {
public:
    generic() {
        std::cout << "Generic Constructor called" << std::endl;
    }
    ~generic() {
        std::cout << "Generic Deconstructor called" << std::endl;
    }
};

class ocean : public generic {
public:
    ocean() {
        std::cout << "Ocean Constructor called" << std::endl;
    }
    ~ocean()  {
        std::cout << "Ocean Deconstructor called" << std::endl;
    }
    void swim() {
        std::cout << "I can swim" << std::endl;
    }
};

class amphibious : public ocean {
public:
    amphibious() {
        std::cout << "Amphibious Constructor called" << std::endl;
    }
    ~amphibious()  {
        std::cout << "Amphibious Deconstructor called" << std::endl;
    }
    void walk() {
        std::cout << "I can walk" << std::endl;
    }
};

class terrestrial : public amphibious {
public:
    terrestrial() {
        std::cout << "Terrestrial Constructor called" << std::endl;
    }
    ~terrestrial()  {
        std::cout << "Terrestrial Deconstructor called" << std::endl;
    }
    void swim() const = delete;
};

class bird : public terrestrial {
public:
    bird() {
        std::cout << "Bird Constructor called" << std::endl;
    }
    ~bird()  {
        std::cout << "Bird Deconstructor called" << std::endl;
    }
    void fly() {
        std::cout << "I can fly" << std::endl;
    }
};

class waterfowl : public bird {
public:
    waterfowl() {
        std::cout << "Waterfowl Constructor called" << std::endl;
    }
    ~waterfowl()  {
        std::cout << "Waterfowl Deconstructor called" << std::endl;
    }
    using ocean::swim;
};

int main() {
    amphibious frog;
    std:: cout <<"\n";

    terrestrial t;
    std:: cout <<"\n";

    bird bird;
    std:: cout <<"\n";

    ocean fish;
    std:: cout <<"\n";

    waterfowl duck;
    std:: cout <<"\n";
}

