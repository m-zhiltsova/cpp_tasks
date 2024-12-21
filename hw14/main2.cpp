#include <iostream>
#include <vector>

class Time {
    static unsigned count;
    int hours;
    int minutes;
    int seconds;
public:
    Time() : hours(0), minutes(0), seconds(0) {
        std::cout << "Time constructor called" << std::endl;
        ++count;
        std::cout << "Created " << count << " object" << (count == 1 ? "" : "s") << std::endl;
    }

    Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
        std::cout << "Time constructor called" << std::endl;
        Normalize();
        ++count;
        std::cout << "Created " << count << " object" << (count == 1 ? "" : "s") << std::endl;
    }

    Time(const Time& t) : hours(t.hours), minutes(t.minutes), seconds(t.seconds) {
        std::cout << "Time copy constructor called" << std::endl;
        ++count;
        std::cout << "Created " << count << " object" << (count == 1 ? "" : "s") << std::endl;
    }

    Time(Time&& t) noexcept : hours(t.hours), minutes(t.minutes), seconds(t.seconds) {
        t.hours = 0;
        t.minutes = 0;
        t.seconds = 0;
        std::cout << "Time move constructor called" << std::endl;
        ++count;
        std::cout << "Created " << count << " object" << (count == 1 ? "" : "s") << std::endl;
    }

    ~Time() {
        std::cout << "Time destructor called" << std::endl;
        --count;
        std::cout << "Now there are " << count << " object" << (count == 1 ? "" : "s") << std::endl;
    }

    Time& operator=(const Time& t) {
        if (this == &t) return *this;
        hours = t.hours;
        minutes = t.minutes;
        seconds = t.seconds;
        std::cout << "Time copy assignment operator called" << std::endl;
        return *this;
    }

    Time& operator=(Time&& t) noexcept {
        if (this == &t) return *this;
        hours = t.hours;
        minutes = t.minutes;
        seconds = t.seconds;
        t.hours = 0;
        t.minutes = 0;
        t.seconds = 0;
        std::cout << "Time move assignment operator called" << std::endl;
        return *this;
    }

    void SetHours(int hours) { this->hours = hours; }
    void SetMinutes(int minutes) { this->minutes = minutes; }
    void SetSeconds(int seconds) { this->seconds = seconds; }

    int GetHours() const { return hours; }
    int GetMinutes() const { return minutes; }
    int GetSeconds() const { return seconds; }

    void PrintTime() const {
        std::cout << "H:" << this->GetHours() << " M:" << this->GetMinutes() << " S:" << this->GetSeconds() << std::endl;
    }

    Time& operator+=(int s) {
        seconds += s;
        Normalize();
        return *this;
    }

    Time& operator-=(int s) {
        seconds -= s;
        Normalize();
        return *this;
    }

    int ToSeconds() const {
        return hours * 60 * 60 + minutes * 60 + seconds;
    }

    void Normalize() {
        int total_seconds = ToSeconds();

        if (total_seconds < 0) {
            total_seconds = (24 * 60 * 60) + (total_seconds % (24 * 60 * 60));
        }

        seconds = total_seconds % 60;
        minutes = (total_seconds / 60) % 60;
        hours = (total_seconds / 3600) % 24;
    }

    void print_count() {
        std::cout << count << std::endl;
    }
};

unsigned Time::count = 0;

Time operator+(const Time& t, int s) {
    return Time(t.GetHours(), t.GetMinutes(), t.GetSeconds() + s);
}

Time operator-(const Time& t, int s) {
    return Time(t.GetHours(), t.GetMinutes(), t.GetSeconds() - s);
}

bool operator==(const Time& t1, const Time& t2) {
    return t1.GetHours() == t2.GetHours()
        && t1.GetMinutes() == t2.GetMinutes()
        && t1.GetSeconds() == t2.GetSeconds();
}

int main() {
    // Демонстрация конструктора перемещения и оператора присваивания с перемещением
    Time t1(1, 2, 3);
    Time t2 = std::move(t1); // Конструктор перемещения
    t1.PrintTime(); // t1 должен быть нулевым
    t2.PrintTime(); // t2 должен быть (1, 2, 3)

    Time t3(4, 5, 6);
    t3 = std::move(t2); // Оператор присваивания с перемещением
    t2.PrintTime(); // t2 должен быть нулевым
    t3.PrintTime(); // t3 должен быть (1, 2, 3)

    // Добавление объектов в vector
    std::vector<Time> times;
    times.push_back(Time(7, 8, 9)); // rvalue
    times.push_back(t3); // lvalue

    // Вывод содержимого вектора
    for (const auto& t : times) {
        t.PrintTime();
    }

    return 0;
}

