#include <iostream>
#include <memory>

// Абстрактный класс продукта - дом
class House {
public:
    virtual void build() const = 0;
    virtual ~House() = default;
};

// Абстрактный класс продукта - забор
class Fence {
public:
    virtual void build() const = 0;
    virtual ~Fence() = default;
};

// Абстрактный класс продукта - сарай
class Barn {
public:
    virtual void build() const = 0;
    virtual ~Barn() = default;
};

// Конкретные реализации продуктов
class WoodHouse : public House {
public:
    void build() const override {
        std::cout << "Building a Wooden House" << std::endl;
    }
};

class BrickHouse : public House {
public:
    void build() const override {
        std::cout << "Building a Brick House" << std::endl;
    }
};

class ConcreteHouse : public House {
public:
    void build() const override {
        std::cout << "Building a Concrete House" << std::endl;
    }
};

class WoodFence : public Fence {
public:
    void build() const override {
        std::cout << "Building a Wooden Fence" << std::endl;
    }
};

class BrickFence : public Fence {
public:
    void build() const override {
        std::cout << "Building a Brick Fence" << std::endl;
    }
};

class ConcreteFence : public Fence {
public:
    void build() const override {
        std::cout << "Building a Concrete Fence" << std::endl;
    }
};

class WoodBarn : public Barn {
public:
    void build() const override {
        std::cout << "Building a Wooden Barn" << std::endl;
    }
};

class BrickBarn : public Barn {
public:
    void build() const override {
        std::cout << "Building a Brick Barn" << std::endl;
    }
};

class ConcreteBarn : public Barn {
public:
    void build() const override {
        std::cout << "Building a Concrete Barn" << std::endl;
    }
};

// Абстрактный класс создатель - застройщик
class Developer {
public:
    virtual std::unique_ptr<House> buildHouse() const = 0;
    virtual std::unique_ptr<Fence> buildFence() const = 0;
    virtual std::unique_ptr<Barn> buildBarn() const = 0;
    virtual ~Developer() = default;
};

// Конкретные реализации застройщика
class WoodDeveloper : public Developer {
public:
    std::unique_ptr<House> buildHouse() const override {
        return std::make_unique<WoodHouse>();
    }

    std::unique_ptr<Fence> buildFence() const override {
        return std::make_unique<WoodFence>();
    }

    std::unique_ptr<Barn> buildBarn() const override {
        return std::make_unique<WoodBarn>();
    }
};

class BrickDeveloper : public Developer {
public:
    std::unique_ptr<House> buildHouse() const override {
        return std::make_unique<BrickHouse>();
    }

    std::unique_ptr<Fence> buildFence() const override {
        return std::make_unique<BrickFence>();
    }

    std::unique_ptr<Barn> buildBarn() const override {
        return std::make_unique<BrickBarn>();
    }
};

class ConcreteDeveloper : public Developer {
public:
    std::unique_ptr<House> buildHouse() const override {
        return std::make_unique<ConcreteHouse>();
    }

    std::unique_ptr<Fence> buildFence() const override {
        return std::make_unique<ConcreteFence>();
    }

    std::unique_ptr<Barn> buildBarn() const override {
        return std::make_unique<ConcreteBarn>();
    }
};

// Функция для демонстрации создания объектов на участке
void buildPlot(const Developer& developer) {
    std::unique_ptr<House> house = developer.buildHouse();
    std::unique_ptr<Fence> fence = developer.buildFence();
    std::unique_ptr<Barn> barn = developer.buildBarn();

    house->build();
    fence->build();
    barn->build();
}

int main() {
    WoodDeveloper woodDeveloper;
    BrickDeveloper brickDeveloper;
    ConcreteDeveloper concreteDeveloper;

    std::cout << "Building with Wood Developer:" << std::endl;
    buildPlot(woodDeveloper);

    std::cout << "Building with Brick Developer:" << std::endl;
    buildPlot(brickDeveloper);

    std::cout << "Building with Concrete Developer:" << std::endl;
    buildPlot(concreteDeveloper);

    return 0;
}

