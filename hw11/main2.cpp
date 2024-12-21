#include <iostream>
#include <vector>
#include <memory>

// Общий родительский класс
class generic {
public:
    generic() {
        std::cout << "Generic Constructor called" << std::endl;
    }
    virtual ~generic() {
        std::cout << "Generic Deconstructor called" << std::endl;
    }

    virtual void eat() = 0; // Чисто виртуальная функция
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

// Наследники Amphibious
class Crocodile : public amphibious {
public:
    Crocodile() {
        std::cout << "Crocodile Constructor called" << std::endl;
    }
    ~Crocodile() {
        std::cout << "Crocodile Deconstructor called" << std::endl;
    }

    void eat() override {
        std::cout << "Crocodile eating legs" << std::endl;
    }
};

class Alligator : public amphibious {
public:
    Alligator() {
        std::cout << "Alligator Constructor called" << std::endl;
    }
    ~Alligator() {
        std::cout << "Alligator Deconstructor called" << std::endl;
    }

    void eat() override {
        std::cout << "Alligator eating arms" << std::endl;
    }
};

// Наследники Bird
class Pigeon : public bird {
public:
    Pigeon() {
        std::cout << "Pigeon Constructor called" << std::endl;
    }
    ~Pigeon() {
        std::cout << "Pigeon Deconstructor called" << std::endl;
    }

    void eat() override {
        std::cout << "Pigeon eating seeds" << std::endl;
    }
};

class Parrot : public bird {
public:
    Parrot() {
        std::cout << "Parrot Constructor called" << std::endl;
    }
    ~Parrot() {
        std::cout << "Parrot Deconstructor called" << std::endl;
    }

    void eat() override {
        std::cout << "Parrot eating fruits" << std::endl;
    }
};

// Наследники Waterfowl
class Duck : public waterfowl {
public:
    Duck() {
        std::cout << "Duck Constructor called" << std::endl;
    }
    ~Duck() {
        std::cout << "Duck Deconstructor called" << std::endl;
    }

    void eat() override {
        std::cout << "Duck eating bread" << std::endl;
    }
};

class Swan : public waterfowl {
public:
    Swan() {
        std::cout << "Swan Constructor called" << std::endl;
    }
    ~Swan() {
        std::cout << "Swan Deconstructor called" << std::endl;
    }

    void eat() override {
        std::cout << "Swan eating plants" << std::endl;
    }
};

// Создатель
class Creator {
public:
    virtual ~Creator() = default;
    virtual generic* createCreature() const = 0;
};

// Конкретные создатели
class CrocodileCreator : public Creator {
public:
    generic* createCreature() const override {
        return new Crocodile();
    }
};

class AlligatorCreator : public Creator {
public:
    generic* createCreature() const override {
        return new Alligator();
    }
};

class PigeonCreator : public Creator {
public:
    generic* createCreature() const override {
        return new Pigeon();
    }
};

class ParrotCreator : public Creator {
public:
    generic* createCreature() const override {
        return new Parrot();
    }
};

class DuckCreator : public Creator {
public:
    generic* createCreature() const override {
        return new Duck();
    }
};

class SwanCreator : public Creator {
public:
    generic* createCreature() const override {
        return new Swan();
    }
};

int main() {
    std::vector<std::unique_ptr<generic>> zoo;

    std::vector<Creator*> creators = {
        new CrocodileCreator(), new CrocodileCreator(), new CrocodileCreator(),
        new AlligatorCreator(), new AlligatorCreator(), new AlligatorCreator(),
        new PigeonCreator(), new PigeonCreator(), new PigeonCreator(),
        new ParrotCreator(), new ParrotCreator(), new ParrotCreator(),
        new DuckCreator(), new DuckCreator(), new DuckCreator(),
        new SwanCreator(), new SwanCreator(), new SwanCreator()
    };

    for (auto creator : creators) {
        zoo.push_back(std::unique_ptr<generic>(creator->createCreature()));
    }

    std::cout << "Feeding all creatures:" << std::endl;
    for (const auto& creature : zoo) {
        creature->eat();
    }

    for (auto creator : creators) {
        delete creator;
    }

    return 0;
}

