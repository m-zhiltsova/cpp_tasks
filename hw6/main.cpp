#include <iostream>
#include <vector>
#include <list>
#include <memory>

class Time
{
    static unsigned count;
    int hours;
    int minutes;
    int seconds;
public:
    Time(int h, int m, int s): hours(h), minutes(m), seconds(s){
        if (((h*3600 + m * 60 + s) < 0) || ((h*3600 + m * 60 + s) > 89999)) {
            throw 0;
        }
        Normalize();
        ++count;
        if (count == 1) {
        std::cout << "Created " << count << " object" << std::endl;
        }
        else {
        std::cout << "Created " << count << " objects" << std::endl;
        }
    };
    ~Time(){
        --count;
        if (count == 1) {
        std::cout << "Now there are " << count << " object" << std::endl;
        }
        else {
        std::cout << "Now there are " << count << " objects" << std::endl;
        }
    };

    int GetHours()   const { return hours;   }
    int GetMinutes() const { return minutes; }
    int GetSeconds() const { return seconds; }

    void PrintTime() {
        std::cout << "H:" << this->GetHours() << " M:" << this->GetMinutes() << " S:" << this->GetSeconds() << std:: endl;
    }

    Time& operator += (int s) {
        seconds += s;
        Normalize();
        return *this;
    }

    Time& operator -= (int s) {
        seconds -= s;
        Normalize();
        return *this;
    }
 
    int ToSeconds() const {
        return hours*60*60 + minutes*60 + seconds;
    };   

    void Normalize() {
        int total_seconds = ToSeconds();

        if (total_seconds < 0) {
            total_seconds = (24 * 60 * 60) + (total_seconds % (24 * 60 * 60)); 
        }

        seconds = total_seconds % 60;
        minutes = (total_seconds / 60) % 60;
        hours = (total_seconds / 3600) % 24;
        };
    void print_count() {
        std::cout << count << std::endl;
    }

};
unsigned Time::count = 0;

Time operator + (const Time& t, int s) {
    return Time(t.GetHours(), t.GetMinutes(), t.GetSeconds() + s);
}

Time operator - (const Time& t, int s) {
    return Time(t.GetHours(), t.GetMinutes(), t.GetSeconds() - s);
}

int main() {
    Time *ptr = new Time(1,1,1);
    delete ptr;
    ptr = nullptr;
    Time *ptr1 = new Time[3] {Time(1, 1, 1), Time(20, 30, 30), Time(20, 30, 20)};
    delete[] ptr1;
    ptr1 = nullptr;

    std::vector<Time> vectortime;
    std::list<Time> listtime;
    vectortime.push_back(Time(14, 45, 3));
    listtime.push_back(Time(9,15, 3)); 

    std::unique_ptr<Time> uniq = std::make_unique<Time>(10,3,2);
    std::shared_ptr<Time> shar = std::make_shared<Time>(11,3,2);
    uniq.reset();
    shar.reset();

    try {
        Time t1(25,3,4);
    }
    catch (int code){
        std::cerr << "Error code: " << code << std::endl;
    }
}
