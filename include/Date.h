#ifndef DATE_H
#define DATE_H

#include <string>

class Date{
    public:
        Date(int year, int month, int day, int hour, int minute, int second);
        virtual ~Date();
        void add(Date date);
        void tick(int second=1);
        std::string toString();
        bool operator <=(const Date& other);
        bool operator <(const Date& other);
        unsigned short int second;
        unsigned short int minute;
        unsigned short int hour;
        unsigned short int day;
        unsigned short int month;
        unsigned int year;
    protected:
    private:
};

#endif // DATE_H
