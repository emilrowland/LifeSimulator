#ifndef DATE_H
#define DATE_H

#include <string>
#include <ostream>

class DeltaTime{
    public:
        DeltaTime(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int minute, unsigned int second);
        unsigned int second;
        unsigned int minute;
        unsigned int hour;
        unsigned int day;
        unsigned int month;
        unsigned int year;
};

class Date{
    public:
        Date(unsigned int year, unsigned short int month, unsigned short int day, unsigned short int hour, unsigned short int minute, unsigned short int second);
        void add(DeltaTime date);
        void tick(unsigned short int second=1);
        std::string toString();
        friend std::ostream& operator<<(std::ostream& os, const Date& dt){
            os << dt.year << "-" << dt.month << "-" << dt.day << " " << dt.hour << ":" << dt.minute << ":" << dt.second;
            return os;
        }
        bool operator <=(const Date& other);
        bool operator <(const Date& other);
        bool operator ==(const Date& other);
        unsigned short int second;
        unsigned short int minute;
        unsigned short int hour;
        unsigned short int day;
        unsigned short int month;
        unsigned int year;
    private:
        int daysInMonth[12] = {32, 29, 32, 31, 32, 31, 32, 32, 31, 32, 31, 32}; //Plus one for faster algorithms
};

#endif // DATE_H
