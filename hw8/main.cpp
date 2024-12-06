#include <iostream>
#include <string>

class GenericCreature {
public:
    std::string name;
    GenericCreature(const std::string& n) : name(n) {
        std::cout << "GenericCreature constructor called for " << name << std::endl;
    }
    virtual ~GenericCreature() {
        std::cout << "GenericCreature destructor called for " << name << std::endl;
    }
    virtual void move() { 
        std::cout << name << " moves." << std::endl;
    }
};

class OceanCreature : public GenericCreature {
public:
    OceanCreature(const std::string& n) : GenericCreature(n) {
        std::cout << "OceanCreature constructor called for " << name << std::endl;
    }
    ~OceanCreature() override {
        std::cout << "OceanCreature destructor called for " << name << std::endl;
    }
    void swim() {
        std::cout << name << " swims." << std::endl;
    }
};

class Amphibious : public OceanCreature {
public:
    Amphibious(const std::string& n) : OceanCreature(n) {
        std::cout << "Amphibious constructor called for " << name << std::endl;
    }
    ~Amphibious() override {
        std::cout << "Amphibious destructor called for " << name << std::endl;
    }
    void walk() {
        std::cout << name << " walks." << std::endl;
    }
};

class TerrestrialCreature : public GenericCreature {
public:
    TerrestrialCreature(const std::string& n) : GenericCreature(n) {
        std::cout << "TerrestrialCreature constructor called for " << name << std::endl;
    }
    ~TerrestrialCreature() override {
        std::cout << "TerrestrialCreature destructor called for " << name << std::endl;
    }
    void walk() {
        std::cout << name << " walks." << std::endl;
    }
};

class Bird : public TerrestrialCreature {
public:
    Bird(const std::string& n) : TerrestrialCreature(n) {
        std::cout << "Bird constructor called for " << name << std::endl;
    }
    ~Bird() override {
        std::cout << "Bird destructor called for " << name << std::endl;
    }
    void fly() {
        std::cout << name << " flies." << std::endl;
    }
};

class Waterfowl : public Bird, public OceanCreature {
public:
    Waterfowl(const std::string& n) : Bird(n), OceanCreature(n) {
        std::cout << "Waterfowl constructor called for " << Bird::name << std::endl;
    }
    ~Waterfowl() override {
        std::cout << "Waterfowl destructor called for " << Bird::name << std::endl;
    }
    void move() override {
        std::cout << Bird::name << " moves on land and water." << std::endl;
    }
};

int main() {
    Waterfowl duck("Donald");
    duck.swim();
    duck.fly();
    duck.walk();
    duck.move();

    Amphibious frog("Froggy");
    frog.swim();
    frog.walk();

    TerrestrialCreature dog("Buddy");
    dog.walk();

    Bird eagle("Eagle");
    eagle.walk();
    eagle.fly();

    return 0;
}

