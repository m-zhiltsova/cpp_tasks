#include <iostream>
#include <memory>
class generic;
class ocean;
class terrestrial;
class amphibious;
class bird;
class waterfowl;

// Интерфейс посетителя
class Visitor {
public:
    virtual void visit(generic& g) = 0;
    virtual void visit(ocean& o) = 0;
    virtual void visit(terrestrial& t) = 0;
    virtual void visit(amphibious& a) = 0;
    virtual void visit(bird& b) = 0;
    virtual void visit(waterfowl& w) = 0;
};

// Базовый класс generic
class generic {
public:
    generic() {
        std::cout << "Generic Constructor called" << std::endl;
    }
    virtual ~generic() {
        std::cout << "Generic Deconstructor called" << std::endl;
    }

    virtual void eat() {
        std::cout << "generic creature eating" << std::endl;
    }

    virtual void accept(Visitor& visitor) {
        visitor.visit(*this);
    }
};

// Класс ocean
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

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }
};

// Класс terrestrial
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

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }
};

// Класс amphibious
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

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }
};

// Класс bird
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

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }
};

// Класс waterfowl
class waterfowl : public bird, public ocean {
public:
    waterfowl() {
        std::cout << "Waterfowl Constructor called" << std::endl;
    }
    ~waterfowl() {
        std::cout << "Waterfowl Deconstructor called" << std::endl;
    }

    void eat() override {
        std::cout << "waterflow creature eating" << std::endl;
    }

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }
};

// Конкретный посетитель для манипуляций с птицами
class BirdVisitor : public Visitor {
public:
    void visit(generic& g) override {
        // Ничего не делаем с generic
    }

    void visit(ocean& o) override {
        // Ничего не делаем с ocean
    }

    void visit(terrestrial& t) override {
        // Ничего не делаем с terrestrial
    }

    void visit(amphibious& a) override {
        // Ничего не делаем с amphibious
    }

    void visit(bird& b) override {
        b.fly();
        b.walk();
    }

    void visit(waterfowl& w) override {
        w.fly();
        w.walk();
        w.swim();
    }
};

// Конкретный посетитель для манипуляций с земноводными
class AmphibiousVisitor : public Visitor {
public:
    void visit(generic& g) override {
        // Ничего не делаем с generic
    }

    void visit(ocean& o) override {
        // Ничего не делаем с ocean
    }

    void visit(terrestrial& t) override {
        // Ничего не делаем с terrestrial
    }

    void visit(amphibious& a) override {
        a.walk();
        a.eat();
        a.swim();
    }

    void visit(bird& b) override {
        // Ничего не делаем с bird
    }

    void visit(waterfowl& w) override {
        // Ничего не делаем с waterfowl
    }
};

int main() {
    bird b;
    amphibious a;
    waterfowl w;

    BirdVisitor birdVisitor;
    AmphibiousVisitor amphibiousVisitor;

    b.accept(birdVisitor);
    a.accept(amphibiousVisitor);
    w.accept(birdVisitor);

    return 0;
}

