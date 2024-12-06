#include <iostream>
#include <string>

class GenericCreature {
public:
    std::string name;
    GenericCreature(const std::string& n) : name(n) {}
    virtual ~GenericCreature() = default;

    void move() {
        std::cout << name << " moves." << std::endl;
    }
};


class OceanCreature : public GenericCreature {
public:
    OceanCreature(const std::string& n) : GenericCreature(n) {}
    void swim() {
        std::cout << name << " swims." << std::endl;
    }
};

class Amphibious : public OceanCreature {
public:
    Amphibious(const std::string& n) : OceanCreature(n) {}
    void walk() {
        std::cout << name << " walks." << std::endl;
    }
};

class TerrestrialCreature : public GenericCreature {
public:
    TerrestrialCreature(const std::string& n) : GenericCreature(n) {}
    void walk() {
        std::cout << name << " walks." << std::endl;
    }
};

class Bird : public TerrestrialCreature {
public:
    Bird(const std::string& n) : TerrestrialCreature(n) {}
    void fly() {
        std::cout << name << " flies." << std::endl;
    }
};

class Waterfowl : public Bird {
public:
  Waterfowl(const std::string& n) : Bird(n) {}
  void swim() {
    std::cout << name << " swims." << std::endl;
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

