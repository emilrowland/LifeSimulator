#ifndef DATE_H
#define DATE_H

#include <string>
#include <ostream>

class DeltaTime{
    public:
        DeltaTime();
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
        Date();
        Date(std::string str);
        Date(unsigned int year, unsigned short int month, unsigned short int day, unsigned short int hour, unsigned short int minute, unsigned short int second);
        Date(const Date& obj);
        void add(DeltaTime date);
        void tick(unsigned short int second=1);
        std::string toString();
        friend std::ostream& operator<<(std::ostream& os, const Date& dt){
            os << dt.year << "-" << dt.month << "-" << dt.day << " " << dt.hour << ":" << dt.minute << ":" << dt.second;
            return os;
        }
        bool operator <=(const Date& other) const;
        bool operator <(const Date& other) const;
        bool operator ==(const Date& other) const;
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
