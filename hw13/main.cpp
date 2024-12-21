#include <iostream>
#include <vector>
#include <string>

// Продукт 1: Дом
class House {
public:
    void addPart(const std::string& part) {
        parts.push_back(part);
    }

    void show() const {
        std::cout << "House parts: ";
        for (const auto& part : parts) {
            std::cout << part << " ";
        }
        std::cout << std::endl;
    }

private:
    std::vector<std::string> parts;
};

// Продукт 2: Документация
class Documentation {
public:
    void addPage(const std::string& page) {
        pages.push_back(page);
    }

    void show() const {
        std::cout << "Documentation pages: ";
        for (const auto& page : pages) {
            std::cout << page << " ";
        }
        std::cout << std::endl;
    }

private:
    std::vector<std::string> pages;
};

// Абстрактный строитель
class Builder {
public:
    virtual ~Builder() = default;
    virtual void buildWalls() = 0;
    virtual void buildFloor() = 0;
    virtual void buildRoof() = 0;
    virtual void buildWindows() = 0;
    virtual void buildDoors() = 0;
    virtual House* getHouse() = 0;
    virtual Documentation* getDocumentation() = 0;
};

// Конкретный строитель
class ConcreteBuilder : public Builder {
public:
    ConcreteBuilder() {
        house = new House();
        documentation = new Documentation();
    }

    ~ConcreteBuilder() {
        delete house;
        delete documentation;
    }

    void buildWalls() override {
        house->addPart("Walls");
        documentation->addPage("Walls documentation");
    }

    void buildFloor() override {
        house->addPart("Floor");
        documentation->addPage("Floor documentation");
    }

    void buildRoof() override {
        house->addPart("Roof");
        documentation->addPage("Roof documentation");
    }

    void buildWindows() override {
        house->addPart("Windows");
        documentation->addPage("Windows documentation");
    }

    void buildDoors() override {
        house->addPart("Doors");
        documentation->addPage("Doors documentation");
    }

    House* getHouse() override {
        return house;
    }

    Documentation* getDocumentation() override {
        return documentation;
    }

private:
    House* house;
    Documentation* documentation;
};

// Директор
class Director {
public:
    void setBuilder(Builder* builder) {
        this->builder = builder;
    }

    void buildMinimalViableProduct() {
        builder->buildWalls();
        builder->buildFloor();
        builder->buildRoof();
    }

    void buildFullFeaturedProduct() {
        builder->buildWalls();
        builder->buildFloor();
        builder->buildRoof();
        builder->buildWindows();
        builder->buildDoors();
    }

private:
    Builder* builder;
};

int main() {
    Director director;
    ConcreteBuilder* builder = new ConcreteBuilder();
    director.setBuilder(builder);

    std::cout << "Building minimal viable product:" << std::endl;
    director.buildMinimalViableProduct();
    builder->getHouse()->show();
    builder->getDocumentation()->show();

    std::cout << "Building full featured product:" << std::endl;
    director.buildFullFeaturedProduct();
    builder->getHouse()->show();
    builder->getDocumentation()->show();

    delete builder;
    return 0;
}

