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
    Time() : hours(0), minutes(0), seconds(0) {
	std::cout << "Default Time constructor called" << std::endl;
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
	std::cout << "Copy Time constructor called" << std::endl;
        ++count;
        if (count == 1) {
        std::cout << "Created " << count << " object" << std::endl;
        }
        else {
        std::cout << "Created " << count << " objects" << std::endl;
        }
    };

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
    void SetHours(int h) {
	    if (h < 0 || h > 23) 
		    throw std::invalid_argument("Invalid hours");
	    hours = h;
    };
    void SetMinutes(int m) {
	    if (m < 0 || m > 59) 
		    throw std::invalid_argument("Invalid minutes");
	    minutes = m;
    };
    void SetSeconds(int s) {
	    if (s < 0 || s > 59)
		    throw std::invalid_argument("Invalid seconds");
	    seconds = s;
    };
    int GetHours()   const noexcept { return hours;   }
    int GetMinutes() const noexcept { return minutes; }
    int GetSeconds() const noexcept { return seconds; }

    void PrintTime() const noexcept {
        std::cout << "H:" << this->GetHours() 
		<< " M:" << this->GetMinutes() 
		<< " S:" << this->GetSeconds() << std:: endl;
    };

    Time& operator += (int s) noexcept {
        seconds += s;
        Normalize();
        return *this;
    };

    Time& operator -= (int s) noexcept {
        seconds -= s;
        Normalize();
        return *this;
    };
 
    int ToSeconds() const noexcept {
        return hours*60*60 + minutes*60 + seconds;
    };   

    void Normalize() noexcept {
        int total_seconds = ToSeconds();

        if (total_seconds < 0) {
            total_seconds = (24 * 60 * 60) + (total_seconds % (24 * 60 * 60)); 
        }

        seconds = total_seconds % 60;
        minutes = (total_seconds / 60) % 60;
        hours = (total_seconds / 3600) % 24;
    };

    void print_count() const noexcept {
        std::cout << count << std::endl;
    };

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
    Time *ptr = new Time(1,1,1);
    delete ptr;
    ptr = nullptr;
    Time *ptr1 = new Time[3] {Time(1, 1, 1), Time(20, 30, 30), Time(20, 30, 20)};
    delete[] ptr1;
    ptr1 = nullptr;

    std::cout << "Создали вектор, использовали push_back" << std::endl;
    std::vector<Time> vectortime;
    vectortime.push_back(Time(14, 45, 3));
    vectortime.push_back(Time(9,15, 3)); 
    vectortime.push_back(Time(9,5, 3)); 
    
    std::cout << "Создали список, использовали push_back" << std::endl;
    std::list<Time> listtime;
    listtime.push_back(Time(9,15, 3)); 
    listtime.push_back(Time(14, 45, 3));
    listtime.push_back(Time(9,5, 3)); 

    std::cout << "Указатели" << std::endl;
    std::unique_ptr<Time> uniq = std::make_unique<Time>(10,3,2);
    std::shared_ptr<Time> shar = std::make_shared<Time>(11,3,2);
    uniq.reset();
    shar.reset();

    Time t1(25,3,4);
    try {
	    t1.SetHours(26);
    }
    catch (const std::invalid_argument& error){
        std::cerr << error.what() << std::endl;
    }
}
