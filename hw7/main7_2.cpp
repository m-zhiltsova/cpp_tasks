#include <iostream>
#include <string>

class Time {
public:
    int hours;
    int minutes;
    int seconds;

    Time(int h = 0, int m = 0, int s = 0) : hours(h), minutes(m), seconds(s) {
        std::cout << "Time constructor called" << std::endl;
    }
    ~Time() {
        std::cout << "Time destructor called" << std::endl;
    }

    void printTime() const {
        std::cout << hours << ":" << minutes << ":" << seconds << std::endl;
    }
    
    void setHours(int h){hours = h;}
    void setMinutes(int m){minutes = m;}
    void setSeconds(int s){seconds = s;}
};

class Clock {
public:
    Time currentTime;
    std::string type;

    Clock(int h = 0, int m = 0, int s = 0, const std::string& t = "Generic Clock") : currentTime(h, m, s), type(t) {
        std::cout << "Clock constructor called for: " << type << std::endl;
    }
    virtual ~Clock() {
        std::cout << "Clock destructor called for: " << type << std::endl;
    }

    virtual void showTime() const {
        std::cout << type << " shows time: ";
        currentTime.printTime();
    }

    virtual void tick() = 0;
};


class CuckooClock : public Clock {
public:
    CuckooClock(int h = 0, int m = 0, int s = 0) : Clock(h, m, s, "Cuckoo Clock") {
        std::cout << "CuckooClock constructor called" << std::endl;
    }
    ~CuckooClock() override {
        std::cout << "CuckooClock destructor called" << std::endl;
    }
    void tick() override {
        std::cout << "Cuckoo! ";
        currentTime.seconds++;
        if (currentTime.seconds >= 60) { currentTime.seconds = 0; currentTime.minutes++; }
        if (currentTime.minutes >= 60) { currentTime.minutes = 0; currentTime.hours++; }
        if (currentTime.hours >= 24) { currentTime.hours = 0; }

    }
};

class WallClock : public Clock {
public:
    std::string material;
    WallClock(int h = 0, int m = 0, int s = 0, const std::string& mat = "Wood") : Clock(h, m, s, "Wall Clock"), material(mat) {
        std::cout << "WallClock constructor called" << std::endl;
    }
    ~WallClock() override {
        std::cout << "WallClock destructor called" << std::endl;
    }
    void tick() override {
        currentTime.seconds++;
        if (currentTime.seconds >= 60) { currentTime.seconds = 0; currentTime.minutes++; }
        if (currentTime.minutes >= 60) { currentTime.minutes = 0; currentTime.hours++; }
        if (currentTime.hours >= 24) { currentTime.hours = 0; }
    }
};

class Watch : public Clock {
public:
    std::string strapMaterial;
    Watch(int h = 0, int m = 0, int s = 0, const std::string& mat = "Leather") : Clock(h, m, s, "Watch"), strapMaterial(mat) {
        std::cout << "Watch constructor called" << std::endl;
    }
    ~Watch() override {
        std::cout << "Watch destructor called" << std::endl;
    }
    void tick() override {
        currentTime.seconds++;
        if (currentTime.seconds >= 60) { currentTime.seconds = 0; currentTime.minutes++; }
        if (currentTime.minutes >= 60) { currentTime.minutes = 0; currentTime.hours++; }
        if (currentTime.hours >= 24) { currentTime.hours = 0; }
    }
};

class SmartWatch : public Watch {
public:
    SmartWatch(int h = 0, int m = 0, int s = 0) : Watch(h, m, s, "Silicone") {
        std::cout << "SmartWatch constructor called" << std::endl;
    }
    ~SmartWatch() override {
        std::cout << "SmartWatch destructor called" << std::endl;
    }
    void showTime() const override {
        std::cout << "SmartWatch shows time: ";
        currentTime.printTime();
    }
    void tick() override {
        currentTime.seconds++;
        if (currentTime.seconds >= 60) { currentTime.seconds = 0; currentTime.minutes++; }
        if (currentTime.minutes >= 60) { currentTime.minutes = 0; currentTime.hours++; }
        if (currentTime.hours >= 24) { currentTime.hours = 0; }

    }
};

int main() {
    CuckooClock cuckoo(10, 30, 45);
    cuckoo.tick();
    cuckoo.showTime();

    WallClock wallClock(11, 0, 0, "Metal");
    wallClock.tick();
    wallClock.showTime();

    Watch watch(12, 0, 0, "Nylon");
    watch.showTime();
    watch.tick();
    watch.showTime();

    SmartWatch smartwatch(1, 2, 3);
    smartwatch.showTime();
    smartwatch.tick();
    smartwatch.showTime();

    return 0;
}

