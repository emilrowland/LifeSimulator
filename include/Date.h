#ifndef DATE_H
#define DATE_H

#include <string>

class Date{
    public:
        Date(unsigned int year, unsigned short int month, unsigned short int day, unsigned short int hour, unsigned short int minute, unsigned short int second);
        virtual ~Date();
        void add(Date date);
        void tick(unsigned short int second=1);
        std::string toString();
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
