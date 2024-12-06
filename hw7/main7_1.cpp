#include <iostream>
#include <string>

class SimpleWatch;
class Time;

class Watch {
    bool is24HourFormat;

public:
    Watch(bool format = true) : is24HourFormat(format) {}
    void PrintTime(const Time& time, bool is24HourFormat);
    void setTime(Time& time, int h, int m, int s);

    void setFormat(bool format) {
        is24HourFormat = format;
    }
};

class Time {
    static unsigned count;
    int hours;
    int minutes;
    int seconds;

public:
    Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
        if (((h * 3600 + m * 60 + s) < 0) || ((h * 3600 + m * 60 + s) > 89999)) {
            throw 0;
        }
        Normalize();
        ++count;
        if (count == 1) {
            std::cout << "Created " << count << " object" << std::endl;
        } else {
            std::cout << "Created " << count << " objects" << std::endl;
        }
    }

    ~Time() {
        --count;
        if (count == 1) {
            std::cout << "Now there are " << count << " object" << std::endl;
        } else {
            std::cout << "Now there are " << count << " objects" << std::endl;
        }
    }

    int GetHours() const { return hours; }
    int GetMinutes() const { return minutes; }
    int GetSeconds() const { return seconds; }

    void PrintTime() {
        std::cout << "H:" << this->GetHours() << " M:" << this->GetMinutes() << " S:" << this->GetSeconds() << std::endl;
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

    void SetHours(int h) { hours = h; Normalize(); }
    void SetMinutes(int m) { minutes = m; Normalize(); }
    void SetSeconds(int s) { seconds = s; Normalize(); }

/*
    void setTime(int h, int m, int s) {
        hours = h;
        minutes = m;
        seconds = s;
        Normalize();
    }
*/
    friend class SimpleWatch;
    friend void Watch::PrintTime(const Time& time, bool is24HourFormat);
    friend void Watch::setTime(Time& time, int h, int m, int s);
};

unsigned Time::count = 0;

void Watch::PrintTime(const Time& time, bool is24HourFormat) {
        if (is24HourFormat) {
            std::cout << time.hours << ":" << time.minutes << ":" << time.seconds << std::endl;
        } else {
            std::string period = (time.hours < 12) ? "AM" : "PM";
            int displayHour = (time.hours == 0) ? 12 : (time.hours > 12 ? time.hours - 12 : time.hours);
            std::cout << displayHour << ":" << time.minutes << ":" << time.seconds << " " << period << std::endl;
        }
    }

void Watch::setTime(Time& time, int h, int m, int s) {
        time.hours = h;
        time.minutes = m;
        time.seconds = s;
        time.Normalize();
    }


// SimpleWatch class
class SimpleWatch {
    bool is24HourFormat;

public:
    SimpleWatch(bool format = true) : is24HourFormat(format) {}

    void PrintTime(const Time& time) {
        if (is24HourFormat) {
            std::cout << time.hours << ":" << time.minutes << ":" << time.seconds << std::endl;
        } else {
            std::string period = (time.hours < 12) ? "AM" : "PM";
            int displayHour = (time.hours == 0) ? 12 : (time.hours > 12 ? time.hours - 12 : time.hours);
            std::cout << displayHour << ":" << time.minutes << ":" << time.seconds << " " << period << std::endl;
        }
    }

    void setTime(Time& time, int h, int m, int s) {
        time.hours = h;
        time.minutes = m;
        time.seconds = s;
        time.Normalize();
    }

    void setFormat(bool format) {
        is24HourFormat = format;
    }
};

int main() {
}
