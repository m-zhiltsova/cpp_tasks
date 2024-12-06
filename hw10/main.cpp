#include <iostream>
#include <vector>

class GenericCreature {
public:
    std::string name;
    GenericCreature(const std::string& n) : name(n) {}
    virtual ~GenericCreature() = default;
    virtual void eat() = 0;
    virtual void move() = 0;
};

class OceanCreature : public GenericCreature {
public:
    OceanCreature(const std::string& n) : GenericCreature(n) {}
    void eat() override { std::cout << name << " eats plankton." << std::endl; }
    void move() override { std::cout << name << " swims." << std::endl; }
    void swim() { std::cout << name << " swims." << std::endl; }
};

class TerrestrialCreature : public GenericCreature {
public:
    TerrestrialCreature(const std::string& n) : GenericCreature(n) {}
    void eat() override { std::cout << name << " eats grass." << std::endl; }
    void move() override { std::cout << name << " walks." << std::endl; }
    void walk() { std::cout << name << " walks." << std::endl; }
};

class Bird : public TerrestrialCreature {
public:
    Bird(const std::string& n) : TerrestrialCreature(n) {}
    void eat() override { std::cout << name << " eats worms." << std::endl; }
    void move() override { std::cout << name << " flies and walks." << std::endl; }
    void fly() { std::cout << name << " flies." << std::endl; }
};

class Waterfowl : public Bird {
public:
    Waterfowl(const std::string& n) : Bird(n) {}
    void eat() override { std::cout << name << " eats fish and plants." << std::endl; }
    void move() override { std::cout << name << " swims, flies and walks." << std::endl; }
    void swim() { std::cout << name << " swims." << std::endl; }
};

class Amphibious : public TerrestrialCreature {
private:
    OceanCreature* oceanCreature;
public:
    Amphibious(const std::string& n) : TerrestrialCreature(n), oceanCreature(new OceanCreature(n)) {}
    ~Amphibious() { delete oceanCreature; }
    void eat() override { std::cout << name << " eats insects and small fish." << std::endl; }
    void move() override { 
        TerrestrialCreature::move();
        oceanCreature->move(); 
    }
    void swim() { oceanCreature->swim(); }

};


int main() {
    std::vector<GenericCreature*> creatures = {
        new OceanCreature("Dolphin"),
        new Amphibious("Frog"),
        new TerrestrialCreature("Cow"),
        new Bird("Eagle"),
        new Waterfowl("Duck")
    };

    for (GenericCreature* creature : creatures) {
        creature->eat();
        creature->move();
        delete creature;
    }

    return 0;
}

