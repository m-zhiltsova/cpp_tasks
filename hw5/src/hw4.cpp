#include <iostream>

class Time
{
    static unsigned count;
    int hours;
    int minutes;
    int seconds;
public:
    Time(int h, int m, int s): hours(h), minutes(m), seconds(s){
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
    Time t1 = {21, 5, 121};
    t1.PrintTime();

    Time t2 = {21, 5, 120};
    t2.PrintTime();
    t2.print_count();
    
    {
        Time t3 = {0, -5, -3600};
        t3.PrintTime();
        t3.print_count();
    }
    t2.print_count();
    
    Time t4 = {21, 5, -120}; 
    t4.PrintTime();
    t4.print_count();
    
    Time t5 = {21, 5, -1};
    t5.PrintTime();
    
    Time t6 = {21, 5, 60};
    t6.PrintTime();
}
