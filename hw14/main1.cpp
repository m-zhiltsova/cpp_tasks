#include <iostream>
#include <memory>

// Интерфейс стратегии
class GearStrategy {
public:
    virtual ~GearStrategy() = default;
    virtual double calculateSpeed(double rpm) const = 0;
};

// Конкретные стратегии для каждой передачи
class Gear1 : public GearStrategy {
public:
    double calculateSpeed(double rpm) const override {
        return rpm * 0.1;
    }
};

class Gear2 : public GearStrategy {
public:
    double calculateSpeed(double rpm) const override {
        return rpm * 0.2;
    }
};

class Gear3 : public GearStrategy {
public:
    double calculateSpeed(double rpm) const override {
        return rpm * 0.3;
    }
};

class Gear4 : public GearStrategy {
public:
    double calculateSpeed(double rpm) const override {
        return rpm * 0.4;
    }
};

class Gear5 : public GearStrategy {
public:
    double calculateSpeed(double rpm) const override {
        return rpm * 0.5;
    }
};

class ReverseGear : public GearStrategy {
public:
    double calculateSpeed(double rpm) const override {
        return -rpm * 0.1; // Отрицательная скорость для заднего хода
    }
};

// Контекст, использующий стратегию
class Car {
public:
    Car(double rpm) : rpm(rpm), currentGear(std::make_unique<Gear1>()) {}

    void setGear(std::unique_ptr<GearStrategy> gear) {
        currentGear = std::move(gear);
    }

    double getSpeed() const {
        return currentGear->calculateSpeed(rpm);
    }

    void setRPM(double rpm) {
        this->rpm = rpm;
    }

private:
    double rpm;
    std::unique_ptr<GearStrategy> currentGear;
};

int main() {
    Car car(2000); // Создаем автомобиль с частотой вращения двигателя 2000 оборотов в минуту

    std::cout << "Speed in Gear 1: " << car.getSpeed() << " km/h" << std::endl;

    car.setGear(std::make_unique<Gear2>());
    std::cout << "Speed in Gear 2: " << car.getSpeed() << " km/h" << std::endl;

    car.setGear(std::make_unique<Gear3>());
    std::cout << "Speed in Gear 3: " << car.getSpeed() << " km/h" << std::endl;

    car.setGear(std::make_unique<Gear4>());
    std::cout << "Speed in Gear 4: " << car.getSpeed() << " km/h" << std::endl;

    car.setGear(std::make_unique<Gear5>());
    std::cout << "Speed in Gear 5: " << car.getSpeed() << " km/h" << std::endl;

    car.setGear(std::make_unique<ReverseGear>());
    std::cout << "Speed in Reverse Gear: " << car.getSpeed() << " km/h" << std::endl;

    return 0;
}

