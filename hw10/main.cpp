#include <iostream>
#include <vector>

// Общий родительский класс
class generic {
public:
    generic() {
        std::cout << "Generic Constructor called" << std::endl;
    }
    virtual ~generic() {
        std::cout << "Generic Deconstructor called" << std::endl;
    }

    virtual void eat() {std::cout << "123" << std::endl;}; // Чистая виртуальная функция
};

// Океаническое существо
class ocean : virtual public generic {
public:
    ocean() {
        std::cout << "Ocean Constructor called" << std::endl;
    }
    ~ocean() {
        std::cout << "Ocean Deconstructor called" << std::endl;
    }

    void swim() {
        std::cout << "I can swim" << std::endl;
    }

    void eat() override {
        std::cout << "ocean creature eating" << std::endl;
    }
};

// Наземное существо
class terrestrial : virtual public generic {
public:
    terrestrial() {
        std::cout << "Terrestrial Constructor called" << std::endl;
    }
    ~terrestrial() {
        std::cout << "Terrestrial Deconstructor called" << std::endl;
    }

    void walk() {
        std::cout << "I can walk" << std::endl;
    }

    void eat() override {
        std::cout << "terrestrial creature eating" << std::endl;
    }
};

// Амфибия
class amphibious : public ocean, public terrestrial {
public:
    amphibious() {
        std::cout << "Amphibious Constructor called" << std::endl;
    }
    ~amphibious() {
        std::cout << "Amphibious Deconstructor called" << std::endl;
    }

    void eat() override {
        std::cout << "amphibious creature eating" << std::endl;
    }
};

// Птица
class bird : virtual public terrestrial {
public:
    bird() {
        std::cout << "Bird Constructor called" << std::endl;
    }
    ~bird() {
        std::cout << "Bird Deconstructor called" << std::endl;
    }

    void fly() {
        std::cout << "I can fly" << std::endl;
    }

    void eat() override {
        std::cout << "bird eating" << std::endl;
    }
};

// Водоплавающая птица
class waterfowl : public bird, public ocean {
public:
    waterfowl() {
        std::cout << "Waterfowl Constructor called" << std::endl;
    }
    ~waterfowl() {
        std::cout << "Waterfowl Deconstructor called" << std::endl;
    }

    void eat() override {
        std::cout << "waterfowl creature eating" << std::endl;
    }
};

int main() {
    std::vector<generic*> creatures;

    creatures.push_back(new ocean());
    creatures.push_back(new terrestrial());
    creatures.push_back(new amphibious());
    creatures.push_back(new bird());
    creatures.push_back(new waterfowl());

    std::cout << " " << std::endl;
    std::cout << " " << std::endl;
    std::cout << "Polymorphic behavior:" << std::endl;
    for (auto creature : creatures) {
        creature->eat();
    }

    std::cout << " " << std::endl;
    std::cout << " " << std::endl;
    std::vector<generic> creatures_ob;
    
    creatures_ob.push_back(ocean());
    creatures_ob.push_back(terrestrial());
    creatures_ob.push_back(amphibious());
    creatures_ob.push_back(bird());
    creatures_ob.push_back(waterfowl());

    std::cout << " " << std::endl;
    std::cout << " " << std::endl;
    for (auto &creature : creatures_ob) {
        creature.eat();
    }

    /*
    std::cout << "\nNon-polymorphic behavior:" << std::endl;
    ocean* oceanCreature = new ocean();
    oceanCreature->swim();
    oceanCreature->eat();

    terrestrial* terrestrialCreature = new terrestrial();
    terrestrialCreature->walk();
    terrestrialCreature->eat();

    amphibious* amphibiousCreature = new amphibious();
    amphibiousCreature->swim();
    amphibiousCreature->walk();
    amphibiousCreature->eat();

    bird* birdCreature = new bird();
    birdCreature->fly();
    birdCreature->walk();
    birdCreature->eat();

    waterfowl* waterfowlCreature = new waterfowl();
    waterfowlCreature->swim();
    waterfowlCreature->fly();
    waterfowlCreature->walk();
    waterfowlCreature->eat();

    */

    for (auto creature : creatures) {
        delete creature;
    }
    /*
    delete oceanCreature;
    delete terrestrialCreature;
    delete amphibiousCreature;
    delete birdCreature;
    delete waterfowlCreature;
    */
    return 0;
}

