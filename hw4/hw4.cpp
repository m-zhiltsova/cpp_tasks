#include <iostream>

class Time
{
    static unsigned count;
    int hours;
    int minutes;
    int seconds;
public:

    Time() : hours(0), minutes(0), seconds(0) {
	std::cout << "Time constructor called" << std::endl;
        ++count;
        if (count == 1) {
        std::cout << "Created " << count << " object" << std::endl;
        }
        else {
        std::cout << "Created " << count << " objects" << std::endl;
        }
    }
    Time(int h, int m, int s): hours(h), minutes(m), seconds(s){
	std::cout << "Time constructor called" << std::endl;
        Normalize();
        ++count;
        if (count == 1) {
        std::cout << "Created " << count << " object" << std::endl;
        }
        else {
        std::cout << "Created " << count << " objects" << std::endl;
        }
    };

    Time(const Time& t) : hours(t.hours), minutes(t.minutes), seconds(t.seconds) {
	std::cout << "Time constructor called" << std::endl;
        ++count;
        if (count == 1) {
        std::cout << "Created " << count << " object" << std::endl;
        }
        else {
        std::cout << "Created " << count << " objects" << std::endl;
        }
    }

    ~Time(){
	std::cout << "Time destructor called" << std::endl;
        --count;
        if (count <= 1) {
        std::cout << "Now there are " << count << " object" << std::endl;
        }
        else {
        std::cout << "Now there are " << count << " objects" << std::endl;
        }
    };

    void SetHours(int hours)     { this->hours = hours;     };
    void SetMinutes(int minutes) { this->minutes = minutes; };
    void SetSeconds(int seconds) { this->seconds = seconds; };


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

bool operator == (const Time& t1, const Time& t2) {
    return t1.GetHours() == t2.GetHours() 
      && t1.GetMinutes() == t2.GetMinutes()
      && t1.GetSeconds() == t2.GetSeconds();
}

int main() {
	/*
	{
    Time t1 = {21, 5, 121};
    t1.PrintTime();

    Time t7 = {21, 5, 120};
    t7.PrintTime();
    t7.print_count();
    
    {
	    t7.SetHours(12);
	    t7.PrintTime();
            Time t7(22, 22, 22);
            t7.PrintTime();
    }
    
    Time t4 = {21, 5, -120}; 
    t4.PrintTime();
    
    Time t5 = {21, 5, -1};
    t5.PrintTime();
    
    Time t6 = {21, 5, 60};
    t6.PrintTime();
	}
	*/
   Time t;
   t.SetHours(1);
   Time t2 = t;
   t2.SetHours(2);
   t2.PrintTime();
   {
       t2.SetHours(12);
       t2.PrintTime();
       Time t2(22, 22, 22);
       t2.PrintTime();
   }
   t2.PrintTime();
   Time t3(3, 3, 3);
   t3 = t;
   t3.SetHours(3);
   t3.PrintTime();

}
