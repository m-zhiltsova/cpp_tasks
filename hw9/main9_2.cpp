#include <iostream>
#include <string>

// переопределяла move, чтобы не было неоднозначности

class GenericCreature {
public:
    std::string name;
    GenericCreature(const std::string& n) : name(n) {}
    virtual ~GenericCreature() = default;
    virtual void move() = 0; 
};

class OceanCreature : public GenericCreature {
public:
    OceanCreature(const std::string& n) : GenericCreature(n) {}
    void swim() { std::cout << name << " swims." << std::endl; }
    void move() override { std::cout << name << " moves in the ocean." << std::endl; }
};

class TerrestrialCreature : public GenericCreature {
public:
    TerrestrialCreature(const std::string& n) : GenericCreature(n) {}
    void walk() { std::cout << name << " walks." << std::endl; }
    void move() override { std::cout << name << " moves on land." << std::endl; }
};

class Bird : public TerrestrialCreature {
public:
    Bird(const std::string& n) : TerrestrialCreature(n) {}
    void fly() { std::cout << name << " flies." << std::endl; }
    void move() override { std::cout << name << " moves in the air and on land." << std::endl; }
};

class Waterfowl : public Bird, public OceanCreature {
public:
    Waterfowl(const std::string& n) : Bird(n), OceanCreature(n) {}
    void move() override { std::cout << Bird::name << " moves in the air, on land, and in water." << std::endl; }
};

int main() {
    Waterfowl duck("Donald");
    duck.swim();
    duck.fly();
    duck.walk();
    duck.move();

    OceanCreature fish("Nemo");
    fish.swim();
    fish.move();

    TerrestrialCreature dog("Buddy");
    dog.walk();
    dog.move();

    Bird eagle("Eagle");
    eagle.fly();
    eagle.walk();
    eagle.move();

    return 0;
}

