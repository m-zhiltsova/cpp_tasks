#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>

// Абстрактный класс House
class House {
public:
    virtual void build() const = 0;
    virtual ~House() = default;
};

// Деревянный дом
class WoodHouse : public House {
public:
    void build() const override {
        std::cout << "Building a Wood House" << std::endl;
    }
};

// Кирпичный дом
class BrickHouse : public House {
public:
    void build() const override {
        std::cout << "Building a Brick House" << std::endl;
    }
};

// Бетонный дом
class ConcreteHouse : public House {
public:
    void build() const override {
        std::cout << "Building a Concrete House" << std::endl;
    }
};

// Абстрактный класс Developer
class Developer {
public:
    virtual std::unique_ptr<House> buildHouse() const = 0;
    virtual ~Developer() = default;
};

// Застройщик деревянных домов
class WoodDeveloper : public Developer {
public:
    std::unique_ptr<House> buildHouse() const override {
        return std::make_unique<WoodHouse>();
    }
};

// Застройщик кирпичных домов
class BrickDeveloper : public Developer {
public:
    std::unique_ptr<House> buildHouse() const override {
        return std::make_unique<BrickHouse>();
    }
};

// Застройщик бетонных домов
class ConcreteDeveloper : public Developer {
public:
    std::unique_ptr<House> buildHouse() const override {
        return std::make_unique<ConcreteHouse>();
    }
};

// Функция для застройки квартала
void buildDistrict(const Developer& developer, int numHouses) {
    std::vector<std::unique_ptr<House>> district;
    for (int i = 0; i < numHouses; ++i) {
        district.push_back(developer.buildHouse());
        district.back()->build();
    }
}

int main() {
    std::srand(std::time(0));

    WoodDeveloper woodDeveloper;
    BrickDeveloper brickDeveloper;
    ConcreteDeveloper concreteDeveloper;

    int numHouses = 4 + std::rand() % 13; // Случайное количество домов от 4 до 16

    std::cout << "Building a district with Wood Houses:" << std::endl;
    buildDistrict(woodDeveloper, numHouses);

    std::cout << "\nBuilding a district with Brick Houses:" << std::endl;
    buildDistrict(brickDeveloper, numHouses);

    std::cout << "\nBuilding a district with Concrete Houses:" << std::endl;
    buildDistrict(concreteDeveloper, numHouses);

    return 0;
}

